{
    "includes": [
        "../common.gypi"
    ],
    "targets": [
        {
            "target_name": "libgdal_mrsid_frmt",
            "type": "static_library",
            "sources": [
                "../gdal/frmts/mrsid/mrsidstream.cpp",
                "../gdal/frmts/mrsid/mrsiddataset.cpp"
            ],
            "include_dirs": [
                "../gdal/frmts/mrsid",
                "../gdal/frmts/gtiff/libgeotiff",
                # The mrsid_include variable needs to be set to the full path of your local lizard tech libs
                "<(mrsid_include)/Raster_DSDK/include"
            ]
        }
    ]
}