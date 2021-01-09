class Vector3 {
public:
    float x;
    float y;
    float z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}
    Vector3(const Vector3 &v);
    ~Vector3();
};
Vector3::Vector3(const Vector3 &v) : x(v.x), y(v.y), z(v.z) {}
Vector3::~Vector3() {}

int GetPlayerTeam(void* player) {
    return *(int*)((uint64_t)player + 0x14);
}

Vector3 get_position(void* transform) {
    if (!transform)
        return Vector3();

    Vector3 position;

    static const auto get_position_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3&)>(getAbsoluteAddress("libil2cpp.so", 0x277913C));//UnityEngine.CoreModule
    get_position_injected(transform, position);

    return position;
}

void set_position(void* transform, Vector3 test) {

    if (transform) {
        static const auto set_position_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3)>(getAbsoluteAddress("libil2cpp.so", 0x27791F4));//UnityEngine.CoreModule
        set_position_injected(transform, test);
    }
}

void* get_transform(void* player) {
    if (!player)
        return NULL;

    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall*)(void*)>(getAbsoluteAddress("libil2cpp.so", 0x1E5DB98));//UnityEngine.CoreModule

    return (void*)get_transform_injected(player);
}

Vector3 GetPlayerLocation(void *player){
    Vector3 location;
    location = get_position(get_transform(player));

    return location;
}

void* myPlayer = NULL;
void *enemyPlayer = NULL;

