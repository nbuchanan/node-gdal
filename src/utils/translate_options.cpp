#include "translate_options.hpp"

namespace node_gdal {

TranslateOptions::TranslateOptions()
{
	options = GDALTranslateOptionsNew(NULL, NULL);
}

TranslateOptions::~TranslateOptions()
{
//    GDALTranslateOptionsFree(options);
	// Don't use: GDALTranslateOptionsFree( options ); - it assumes ownership of everything
	if (options) delete options;
}

int TranslateOptions::parse(Local<Value> value)
{
	Nan::HandleScope scope;

	if (!value->IsObject() || value->IsNull())
		Nan::ThrowTypeError("Translate options must be an object");

	Local<Object> obj = value.As<Object>(), obj2;
	Local<Value> prop, prop2;

    // Output format
    if (obj->HasOwnProperty(Nan::New("outputFormat").ToLocalChecked())) {
        prop = obj->Get(Nan::New("outputFormat").ToLocalChecked());
        if (!prop->IsString()) {
            Nan::ThrowTypeError("outputFormat property must be a string");
            return 1;
        }
        std::string stringVal = *Nan::Utf8String(prop);
        options->pszFormat = (char*) stringVal.c_str();
    }

    // Projected window to clip by
    if (obj->HasOwnProperty(Nan::New("projWin").ToLocalChecked())) {
        prop = obj->Get(Nan::New("projWin").ToLocalChecked());
        if (prop->IsObject()) {
            obj2 = prop->ToObject();
            // Assume if minX property is present the other three envelope values are
            if (obj2->HasOwnProperty(Nan::New("minX").ToLocalChecked())) {
                prop2 = obj2->Get(Nan::New("minX").ToLocalChecked());
                if (prop2->IsNumber() && !prop2->IsNull()) {
                    options->dfULX = prop2->NumberValue();
                } else {
                    Nan::ThrowTypeError("projWin envelope object must have minX number property"); return 1;
                }

                // TODO make this more robust
                options->dfLRY = obj2->Get(Nan::New("minY").ToLocalChecked())->NumberValue();
                options->dfLRX = obj2->Get(Nan::New("maxX").ToLocalChecked())->NumberValue();
                options->dfULY = obj2->Get(Nan::New("maxY").ToLocalChecked())->NumberValue();
            }
        } else {
            Nan::ThrowTypeError("projWin property must be envelope object"); return 1;
        }
    }

    // Projected window spatial reference system
    if (obj->HasOwnProperty(Nan::New("projWinSRS").ToLocalChecked())) {
        prop = obj->Get(Nan::New("projWinSRS").ToLocalChecked());
        if (!prop->IsString()) {
            Nan::ThrowTypeError("projWinSRS property must be any of the usual GDAL/OGR forms, complete WKT, PROJ.4, EPSG:n or a file containing the WKT");
            return 1;
        } else {
            std::string stringVal = *Nan::Utf8String(prop);
            options->pszProjSRS = (char*) stringVal.c_str();
        }
    }

    // TODO Add additional translate options

    return 0;
}

}