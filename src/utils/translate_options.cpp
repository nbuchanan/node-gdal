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

	Local<Object> obj = value.As<Object>();
	Local<Value> prop;

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

    // TODO Add additional translate options

    return 0;
}

}