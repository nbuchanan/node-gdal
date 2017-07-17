var gdal = require('../lib/gdal.js');
var path = require('path');
var assert = require('chai').assert;

if (process.env.TARGET !== 'SHARED') {
	describe('Open', function() {
		describe('MrSID', function() {
			var filename, ds;

			it('should not throw', function() {
				filename = path.join(__dirname, 'data/UniformColorBalancedMosaic.sid');
				ds = gdal.open(filename);
			});

			it('should be able to read raster size', function() {
				assert.equal(ds.rasterSize.x, 10000);
				assert.equal(ds.rasterSize.y, 10000);
				assert.equal(ds.bands.count(), 3);
			});

            it('should be able to read geotransform', function() {
                var expected_geotransform = [ 548900,0.30000000004656613,0,5275200,0,-0.2999999998137355 ];

                var actual_geotransform = ds.geoTransform;
                var delta = 0.00001;
                assert.closeTo(actual_geotransform[0], expected_geotransform[0], delta);
                assert.closeTo(actual_geotransform[1], expected_geotransform[1], delta);
                assert.closeTo(actual_geotransform[2], expected_geotransform[2], delta);
                assert.closeTo(actual_geotransform[3], expected_geotransform[3], delta);
                assert.closeTo(actual_geotransform[4], expected_geotransform[4], delta);
                assert.closeTo(actual_geotransform[5], expected_geotransform[5], delta);
            });

            it('should have projection', function() {
                assert.match(ds.srs.toWKT(), /PROJCS/);
            });
		});
	});
}
