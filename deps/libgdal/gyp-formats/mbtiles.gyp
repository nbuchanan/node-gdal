{
	"includes": [
		"../common.gypi"
	],
	"targets": [
		{
			"target_name": "libgdal_mbtiles_frmt",
			"type": "static_library",
			"sources": [
                "../gdal/frmts/mbtiles/mbtilesdataset.cpp"
			],
			"include_dirs": [
                "<(SHARED_INTERMEDIATE_DIR)/sqlite-autoconf-<@(sqlite_version)",
                "../gdal/ogr/ogrsf_frmts/sqlite",
                "../gdal/ogr/ogrsf_frmts/gpkg",
                "../gdal/frmts/mbtiles"
			]
		}
	]
}
