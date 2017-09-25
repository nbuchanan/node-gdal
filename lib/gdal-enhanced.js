#!/usr/bin/env node

'use strict';

const MODULE_NAME = 'gdal-enhanced';

var gdal = require('..'),
    fs = require('fs'),
    path = require('path'),
    logger = require('loglevel').noConflict().getLogger(MODULE_NAME);

logger.setLevel('DEBUG');

var getRasterInfo = function(rds) {
  logger.debug('number of bands: ' + rds.bands.count());
  logger.debug('width: ' + rds.rasterSize.x);
  logger.debug('height: ' + rds.rasterSize.y);
  logger.debug('geotransform: ' + rds.geoTransform);
  logger.debug('srs: ' + (rds.srs ? rds.srs.toWKT() : 'null'));
};

var getRasterBBox = function(rds) {
  // raster dimensions
  var size = rds.rasterSize;

  // geotransform
  var geotransform = rds.geoTransform;

  // corners
  var corners = {
    'UpperLeft': {x: 0, y: 0},
    'UpperRight': {x: size.x, y: 0},
    'BottomRight': {x: size.x, y: size.y},
    'BottomLeft': {x: 0, y: size.y},
    'Center': {x: size.x / 2, y: size.y / 2},
  };

  var wgs84 = gdal.SpatialReference.fromEPSG(4326);
  var coord_transform = new gdal.CoordinateTransformation(rds.srs, wgs84);

  var footprint_map = {};
  var corner_names = Object.keys(corners);
  corner_names.forEach(function(corner_name) {
    // convert pixel x,y to the coordinate system of the raster
    // then transform it to WGS84
    var corner = corners[corner_name];
    var pt_orig = {
      x: geotransform[0] + corner.x * geotransform[1] +
      corner.y * geotransform[2],
      y: geotransform[3] + corner.x * geotransform[4] +
      corner.y * geotransform[5],
    };
    var pt_wgs84 = coord_transform.transformPoint(pt_orig);
    footprint_map[corner_name] = {
      'lat': pt_wgs84.y,
      'lng': pt_wgs84.x,
    };
  });

  var bbox =
      [
        [
          [footprint_map['BottomLeft'].lng, footprint_map['BottomLeft'].lat],
          [footprint_map['UpperLeft'].lng, footprint_map['UpperLeft'].lat],
          [footprint_map['UpperRight'].lng, footprint_map['UpperRight'].lat],
          [footprint_map['BottomRight'].lng, footprint_map['BottomRight'].lat],
          [footprint_map['BottomLeft'].lng, footprint_map['BottomLeft'].lat],
        ]];

  logger.debug(bbox);
};

if (require.main === module) {

  var baseAppName = path.basename(__filename, path.extname(__filename));

  // Parse arguments
  var argv = require('yargs').
      usage('Usage: ' + baseAppName + ' <command> [options]').
      command('info',
          'Attempt to get geospatially relevant metadata for a file using GDAL').
      example(baseAppName + ' info -f back40.tif',
          'Print metadata for a GeoTIFF').
      alias('f', 'file').
      nargs('f', 1).
      describe('f', 'File of interest').
      demandOption(['f']).
      describe('d', 'List currently registered drivers').
      alias('d', 'drivers').
      help('h').
      alias('h', 'help').
      epilog('copyright 1984').argv;

  if (argv.drivers) {
    // List currently configured drivers
    logger.debug('Currently supported GDAL drivers: ' +
        gdal.drivers.getNames());
  }

  if (!fs.existsSync(argv.file)) {
    logger.error(argv.file + ' is not a valid file.');
    return;
  }

  var dataset = gdal.open(argv.file);
  // TODO Error handling

  var driver = dataset.driver;
  logger.debug('Used ' + driver.description + ' driver to open dataset');
  if (driver.getMetadata()['DCAP_RASTER'] !== 'YES') {
    logger.info('Source file is not a raster. Treating as a vector and attempting to inspect first layer.');
    // TODO What to do here?
    var layer = dataset.layers.get(0);
    logger.debug('number of features: ' + layer.features.count());
    logger.debug('fields: ' + layer.fields.getNames());
    logger.debug('extent: ' + JSON.stringify(layer.extent));
    logger.debug('srs: ' + (layer.srs ? layer.srs.toWKT() : 'null'));
  } else {
    // gdal.config('GDAL_DATA', path.join(process.cwd(), 'lib/gdal-data'));
    // gdal.setConfigOption('GDAL_DATA', path.join(process.cwd(), 'gdal-data'));
    getRasterInfo(dataset);
    getRasterBBox(dataset);
  }

} else {
  logger.debug(MODULE_NAME + ' required as a module');
}