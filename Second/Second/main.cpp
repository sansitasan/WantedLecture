#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <typeindex>

class IVariantItem
{
public:
    virtual ~IVariantItem() {}

public:
    virtual void* GetItem() = 0;
    virtual const std::type_info& GetType() const = 0;
};

template<typename T>
class VariantItem : public IVariantItem
{
public:
    VariantItem(const T& val) : Value(val) {}

public:
    ~VariantItem() override = default;

public:
    void* GetItem() override {
        return &Value;
    }

    const std::type_info& GetType() const override {
        return typeid(T);
    }

private:
    T Value;
};

template<typename... Types>
class Variants
{
public:
    Variants() {}

    Variants(const Types&... arg) : ValueCount(sizeof...(arg)) {
        GetTotalSize(0, arg...);
        ConstructItems(0, 0, arg...);
    }

    ~Variants() {
        for (int i = 0; i < ValueCount; ++i) {
            Items[i]->~IVariantItem();
        }
        free(Values);
    }

    template<typename T>
    T GetValue() const {
        for (int i = 0; i < ValueCount; ++i) {
            if (Items[i]->GetType() == typeid(T)) return *static_cast<T*>(Items[i]->GetItem());
        }

        throw std::runtime_error("Type not Exist");
    }

private:
    void AllocMemory(unsigned int totalSize) {
        Values = static_cast<char*>(malloc(totalSize));
        if (!Values) {
            throw std::bad_alloc();
        }
    }

    template<typename T, typename... Ts>
    void GetTotalSize(unsigned int totalSize, const T& t, const Ts&... args) {
        totalSize += sizeof(VariantItem<T>);
        GetTotalSize(totalSize, args...);
    }

    void GetTotalSize(unsigned int totalSize) {
        AllocMemory(totalSize);
    }

    template<typename T, typename... Ts>
    void ConstructItems(unsigned int index, unsigned int prevSize, const T& t, const Ts&... args) {
        Items[index] = new(Values + prevSize) VariantItem<T>(t);
        ConstructItems(index + 1, prevSize + sizeof(VariantItem<T>), args...);
    }

    void ConstructItems(unsigned int index, unsigned int prevSize) {}

    char* Values = nullptr;

    int ValueCount = 0;

    IVariantItem* Items[sizeof...(Types)] = {};
};

#define MAKE_VARIANTS_1(name, type0, value0) \
    Variants<type0> name(value0);

#define MAKE_VARIANTS_2(name, type0, value0, type1, value1) \
    Variants<type0, type1> name(value0, value1);

#define MAKE_VARIANTS_3(name, type0, value0, type1, value1, type2, value2) \
    Variants<type0, type1, type2> name(value0, value1, value2);

#define MAKE_VARIANTS_4(name, type0, value0, type1, value1, type2, value2, type3, value3) \
    Variants<type0, type1, type2, type3> name(value0, value1, value2, value3);

#define MAKE_VARIANTS_5(name, type0, value0, type1, value1, type2, value2, type3, value3, type4, value4) \
    Variants<type0, type1, type2, type3, type4> name(value0, value1, value2, value3, value4);

#define GET_VARIANT_ITEM(variants, type, value) \
    value = variants.GetValue<type>();

int main() {
    int a = 0;
    double b = 1.0;
    int* c = &a;
    std::string str = "Hello";

    MAKE_VARIANTS_5(inst, int, a, double, b, int*, c, std::string, str, char, 'x');

    int ra = -1;
    double rb = -2;
    int* rc = nullptr;
    std::string rs = "";
    char rch = '0';

    GET_VARIANT_ITEM(inst, int, ra);
    GET_VARIANT_ITEM(inst, double, rb);
    GET_VARIANT_ITEM(inst, int*, rc);
    GET_VARIANT_ITEM(inst, std::string, rs);
    GET_VARIANT_ITEM(inst, char, rch);

    assert(ra == a);
    assert(rb == b);
    assert(rc == c);
    assert(rs == str);
    assert(rch == 'x');

    std::cout << "Success" << std::endl;

    return 0;
}