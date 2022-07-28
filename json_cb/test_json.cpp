//
// Created by leolaxie on 2022/7/28.
//

//
// Created by leolaxie on 2022/7/27.
//

#include <stdio.h>
#include <vector>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace std;
using namespace rapidjson;

rapidjson::StringBuffer buf;
rapidjson::Writer<rapidjson::StringBuffer> writer(buf);

void serialize01()
{
    buf.Clear();
    writer.StartObject();
    {
        writer.Key("test");
        writer.StartObject();
        {
            writer.Key("k1");
            writer.String("v1");
        }
        writer.EndObject();
    }
    writer.EndObject();

    printf("%s\n", buf.GetString());
}

void serialize02()
{
    buf.Clear();
    writer.Reset(buf);
    writer.StartObject();
    {
        writer.Key("test");
        writer.StartArray();
        {
            writer.String("1");
            writer.String("YI\'E");
        }
        writer.EndArray();
    }
    writer.EndObject();

    printf("%s\n", buf.GetString());
}

/**
 * schema:
 *
 * */
int deserialize01()
{
    const char *input = "{\n"
                        "  \"code\": 0,\n"
                        "  \"msg\": \"\",\n"
                        "  \"resultMap\": {\n"
                        "    \"183.14.30.185\": {\n"
                        "      \"foreign\": false,\n"
                        "      \"country\": \"中国\",\n"
                        "      \"province\": \"广东省\",\n"
                        "      \"city\": \"深圳市\",\n"
                        "      \"district\": \"\",\n"
                        "      \"front_isp\": \"\",\n"
                        "      \"backbone_isp\": \"\",\n"
                        "      \"country_code\": \"\",\n"
                        "      \"district_code\": \"\"\n"
                        "    },\n"
                        "    \"42.194.235.210\": {\n"
                        "      \"foreign\": false,\n"
                        "      \"country\": \"中国\",\n"
                        "      \"province\": \"上海市\",\n"
                        "      \"city\": \"上海市\",\n"
                        "      \"district\": \"\",\n"
                        "      \"front_isp\": \"\",\n"
                        "      \"backbone_isp\": \"\",\n"
                        "      \"country_code\": \"\",\n"
                        "      \"district_code\": \"\"\n"
                        "    }\n"
                        "  }\n"
                        "}";
    Document doc;
    doc.Parse(input);
    auto iter = doc.FindMember("resultMap");
    if (iter == doc.MemberEnd() || !iter->value.IsObject())
        return printf("nofound");
    for (const auto &item: iter->value.GetObject())
    {
        printf("ip: %s\n", item.name.GetString());
        auto loca = item.value.GetObject();
        printf("%s\n", loca["country"].GetString());
    }
    return 0;
}

int main()
{
    deserialize01();
}