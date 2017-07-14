{
    "includes": [
        "../common.gypi"
    ],
    "targets": [
        {
            "target_name": "libgdal_mrsid_lidar_frmt",
            "type": "static_library",
            "sources": [
                "../gdal/frmts/mrsid_lidar/gdal_MG4Lidar.cpp"
            ],
            "include_dirs": [
                "../gdal/frmts/mrsid_lidar",
                "../gdal/frmts/gtiff/libgeotiff",
                # The mrsid_include variable needs to be set to the full path of your local lizard tech libs
                "<(mrsid_include)/Lidar_DSDK/include"
            ]
        }
    ]
}