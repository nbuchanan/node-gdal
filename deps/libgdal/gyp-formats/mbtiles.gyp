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
                "../../../build/Release/obj/global_intermediate/sqlite-autoconf-3150000",
			    "../gdal/ogr/ogrsf_frmts/sqlite",
			    "../gdal/ogr/ogrsf_frmts/gpkg",
				"../gdal/frmts/mbtiles"
			]
		}
	]
}
