{
	"includes": [
		"../common.gypi"
	],
	"targets": [
		{
			"target_name": "libgdal_ogr_sqlite_frmt",
			"type": "static_library",
			"sources": [
			    # Do not include ogrsqliteregexp.cpp or ogrsqlitesqlfunctions.cpp (cannot be compiled directly)
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqliteapiroutines.c",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitedatasource.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitedriver.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqliteexecutesql.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitelayer.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqliteselectlayer.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitesinglefeaturelayer.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitetablelayer.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitevfs.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqliteviewlayer.cpp",
				"../gdal/ogr/ogrsf_frmts/sqlite/ogrsqlitevirtualogr.cpp",
				# "../gdal/ogr/ogrsf_frmts/sqlite/test_load_virtual_ogr.c"
			],
			"include_dirs": [
			    "../../../build/Release/obj/global_intermediate/sqlite-autoconf-3150000",
				"../gdal/ogr/ogrsf_frmts/sqlite"
			]
		}
	]
}
