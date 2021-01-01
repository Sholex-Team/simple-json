
#ifndef SIMPLE_JSON_JSON_PATCH_H
#define SIMPLE_JSON_JSON_PATCH_H


namespace simple_json::types {
    class Json;

    class JsonPatch {
    private:
        Json * patch;
    public:

        // Constructors
        JsonPatch(const Json &);
        JsonPatch(const JsonPatch &);
        JsonPatch(JsonPatch &&) noexcept;

        // Destructors
        ~JsonPatch();

        // Public Method
        void action(Json &);
    };
}


#endif //SIMPLE_JSON_JSON_PATCH_H
