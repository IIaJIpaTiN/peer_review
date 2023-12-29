#include <string>

using namespace std;

class CityBuilder {
public:
    CityBuilder& SetName(string name) {
        name_ = std::move(name);
        return *this;
    }

    CityBuilder& SetIsoCode(string iso_code) {
        iso_code_ = std::move(iso_code);
        return *this;
    }

    CityBuilder& SetPhoneCode(string phone_code) {
        phone_code_ = std::move(phone_code);
        return *this;
    }

    CityBuilder& SetCountry(const Country& country) {
        country_ = country;
        return *this;
    }

    City Build() {
        return {
            name_,
            iso_code_,
            country_.phone_code + phone_code_,
            country_.name,
            country_.iso_code,
            country_.time_zone,
            country_.languages
        }
    }

private:
    string name_;
    string iso_code_;
    string phone_code_;
    Country& country_;
};

void ParseCountryJson(vector<Country>& countries, vector<City>& cities, const Json& json) {
    for (const auto& country_json : json.AsList()) {
        const auto& country_obj = country_json.AsObject();
        countries.push_back({
                                country_obj["name"s].AsString(),
                                country_obj["iso_code"s].AsString(),
                                country_obj["phone_code"s].AsString(),
                                country_obj["time_zone"s].AsString(),
                            });

        Country& country = countries.back();
        for (const auto& lang_obj : country_obj["languages"s].AsList()) {
            country.languages.push_back(FromString<Language>(lang_obj.AsString()));
        }

        for (const auto& city_json : country_obj["cities"s].AsList()) {
            const auto& city_obj = city_json.AsObject();
            cities.push_back(
                    CityBuilder()
                        .SetCountry(country)
                        .SetName(city_obj["name"s].AsString())
                        .SetIsoCode(city_obj["iso_code"s].AsString())
                        .SetPhoneCode(city_obj["phone_code"s].AsString())
                        .Build()
                    );
        }
    }
}