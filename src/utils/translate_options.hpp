
#ifndef __TRANSLATE_OPTIONS_H__
#define __TRANSLATE_OPTIONS_H__

// node
#include <node.h>

// nan
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <nan.h>
#pragma GCC diagnostic pop

// gdal
#include <gdal_utils.h>

using namespace v8;

typedef enum
{
    MASK_DISABLED,
    MASK_AUTO,
    MASK_USER
} MaskMode;


// scaling parameters for use in GDALTranslateOptions.
typedef struct
{
    /*! scaling is done only if it is set to TRUE. This is helpful when there is a need to
        scale only certain bands. */
    int     bScale;

    /*! set it to TRUE if dfScaleSrcMin and dfScaleSrcMax is set. When it is FALSE, the
        input range is automatically computed from the source data. */
    int     bHaveScaleSrc;

    /*! the range of input pixel values which need to be scaled */
    double  dfScaleSrcMin, dfScaleSrcMax;

    /*! the range of output pixel values. If GDALTranslateScaleParams::dfScaleDstMin
        and GDALTranslateScaleParams::dfScaleDstMax are not set, then the output
        range is 0 to 255. */
    double  dfScaleDstMin, dfScaleDstMax;
} GDALTranslateScaleParams;

// Options for use with GDALTranslate().
struct GDALTranslateOptions
{

    /*! output format. The default is GeoTIFF(GTiff). Use the short format name. */
    char *pszFormat;

    /*! allow or suppress progress monitor and other non-error output */
    int bQuiet;

    /*! the progress function to use */
    GDALProgressFunc pfnProgress;

    /*! pointer to the progress data variable */
    void *pProgressData;

    /*! for the output bands to be of the indicated data type */
    GDALDataType eOutputType;

    MaskMode eMaskMode;

    /*! number of input bands to write to the output file, or to reorder bands */
    int nBandCount;

    /*! list of input bands to write to the output file, or to reorder bands. The
        value 1 corresponds to the 1st band. */
    int *panBandList; /* negative value of panBandList[i] means mask band of ABS(panBandList[i]) */

    /*! size of the output file. GDALTranslateOptions::nOXSizePixel is in pixels and
        GDALTranslateOptions::nOYSizePixel is in lines. If one of the two values is
        set to 0, its value will be determined from the other one, while maintaining
        the aspect ratio of the source dataset */
    int nOXSizePixel;
    int nOYSizePixel;

    /*! size of the output file. GDALTranslateOptions::dfOXSizePct and GDALTranslateOptions::dfOYSizePct
        are fraction of the input image size. The value 100 means 100%. If one of the two values is set
        to 0, its value will be determined from the other one, while maintaining the aspect ratio of the
        source dataset */
    double dfOXSizePct;
    double dfOYSizePct;

    /*! list of creation options to the output format driver */
    char **papszCreateOptions;

    /*! subwindow from the source image for copying based on pixel/line location */
    double adfSrcWin[4];

    /*! don't be forgiving of mismatches and lost data when translating to the output format */
    int bStrict;

    /*! apply the scale/offset metadata for the bands to convert scaled values to unscaled values.
     *  It is also often necessary to reset the output datatype with GDALTranslateOptions::eOutputType */
    int bUnscale;

    /*! the size of pasScaleParams */
    int nScaleRepeat;

    /*! the list of scale parameters for each band. */
    GDALTranslateScaleParams *pasScaleParams;

    /*! It is set to TRUE, when scale parameters are specific to each band */
    int bHasUsedExplicitScaleBand;

    /*! the size of the list padfExponent */
    int nExponentRepeat;

    /*! to apply non-linear scaling with a power function. It is the list of exponents of the power
        function (must be positive). This option must be used with GDALTranslateOptions::pasScaleParams. If
        GDALTranslateOptions::nExponentRepeat is 1, it is applied to all bands of the output image. */
    double *padfExponent;

    int bHasUsedExplicitExponentBand;

    /*! list of metadata key and value to set on the output dataset if possible.
     *  GDALTranslateOptionsSetMetadataOptions() and GDALTranslateOptionsAddMetadataOptions()
     *  should be used */
    char **papszMetadataOptions;

    /*! override the projection for the output file. The SRS may be any of the usual
        GDAL/OGR forms, complete WKT, PROJ.4, EPSG:n or a file containing the WKT. */
    char *pszOutputSRS;

    /*! number of GCPS to be added to the output dataset */
    int nGCPCount;

    /*! list of GCPs to be added to the output dataset */
    GDAL_GCP *pasGCPs;

    /*! assign/override the georeferenced bounds of the output file. This assigns
        georeferenced bounds to the output file, ignoring what would have been
        derived from the source file. So this does not cause reprojection to the
        specified SRS. */
    double adfULLR[4];

    /*! set a nodata value specified in GDALTranslateOptions::dfNoDataReal to the output bands */
    int bSetNoData;

    /*! avoid setting a nodata value to the output file if one exists for the source file */
    int bUnsetNoData;

    /*! Assign a specified nodata value to output bands ( GDALTranslateOptions::bSetNoData option
        should be set). Note that if the input dataset has a nodata value, this does not cause
        pixel values that are equal to that nodata value to be changed to the value specified. */
    double dfNoDataReal;

    /*! to expose a dataset with 1 band with a color table as a dataset with
        3 (RGB) or 4 (RGBA) bands. Useful for output drivers such as JPEG,
        JPEG2000, MrSID, ECW that don't support color indexed datasets.
        The 1 value enables to expand a dataset with a color table that only
        contains gray levels to a gray indexed dataset. */
    int nRGBExpand;

    int nMaskBand; /* negative value means mask band of ABS(nMaskBand) */

    /*! force recomputation of statistics */
    int bStats;

    int bApproxStats;

    /*! If this option is set, GDALTranslateOptions::adfSrcWin or (GDALTranslateOptions::dfULX,
        GDALTranslateOptions::dfULY, GDALTranslateOptions::dfLRX, GDALTranslateOptions::dfLRY)
        values that falls partially outside the source raster extent will be considered
        as an error. The default behaviour is to accept such requests. */
    int bErrorOnPartiallyOutside;

    /*! Same as bErrorOnPartiallyOutside, except that the criterion for
        erroring out is when the request falls completely outside the
        source raster extent. */
    int bErrorOnCompletelyOutside;

    /*! does not copy source RAT into destination dataset (when TRUE) */
    int bNoRAT;

    /*! resampling algorithm
        nearest (default), bilinear, cubic, cubicspline, lanczos, average, mode */
    char *pszResampling;

    /*! target resolution. The values must be expressed in georeferenced units.
        Both must be positive values. This is exclusive with GDALTranslateOptions::nOXSizePixel
        (or GDALTranslateOptions::dfOXSizePct), GDALTranslateOptions::nOYSizePixel
        (or GDALTranslateOptions::dfOYSizePct) and GDALTranslateOptions::adfULLR */
    double dfXRes;
    double dfYRes;

    /*! subwindow from the source image for copying (like GDALTranslateOptions::adfSrcWin)
        but with the corners given in georeferenced coordinates (by default
        expressed in the SRS of the dataset. Can be changed with
        pszProjSRS) */
    double dfULX;
    double dfULY;
    double dfLRX;
    double dfLRY;

    /*! SRS in which to interpret the coordinates given with GDALTranslateOptions::dfULX,
        GDALTranslateOptions::dfULY, GDALTranslateOptions::dfLRX, GDALTranslateOptions::dfLRY.
        The SRS may be any of the usual GDAL/OGR forms, complete WKT, PROJ.4, EPSG:n or
        a file containing the WKT. Note that this does not cause reprojection of the
        dataset to the specified SRS. */
    char *pszProjSRS;

};

namespace node_gdal {

// A class for parsing a V8::Value and constructing a GDALTranslateOptions struct
//
// see: http://www.gdal.org/gdal__utils_8h.html#a824ae5ddbd5058bb317501bd25219dd4
//
// {
//   src: Dataset
//   dst: string
//   outputFormat : string
// }

class TranslateOptions {
public:
	int parse(Local<Value> value);

	TranslateOptions();
	~TranslateOptions();

	inline GDALTranslateOptions* get() {
		return options;
	}
private:
	GDALTranslateOptions *options;
};

}

#endif