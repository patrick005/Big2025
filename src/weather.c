// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// // #include <curl/curl.h>
// // #include <jansson.h>

// #define API_KEY "bd051b188f6b1a86175dbb65aa1f5100" // OpenWeatherMap API 키를 입력하세요.
// #define CITY_ID "1846095" // 세종시 ID (OpenWeatherMap에서 확인 가능)

// // API 응답 데이터를 저장할 구조체
// struct MemoryStruct {
//     char *memory;
//     size_t size;
// };

// // API 응답 데이터를 메모리에 저장하는 콜백 함수
// static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
//     size_t realsize = size * nmemb;
//     struct MemoryStruct *mem = (struct MemoryStruct *)userp;

//     char *ptr = realloc(mem->memory, mem->size + realsize + 1);
//     if (ptr == NULL) {
//         printf("메모리 할당 실패!\n");
//         return 0;
//     }

//     mem->memory = ptr;
//     memcpy(&(mem->memory[mem->size]), contents, realsize);
//     mem->size += realsize;
//     mem->memory[mem->size] = 0;

//     // // JSON 원본 데이터 출력 (디버깅용)
//     // printf("JSON 원본:\n%s\n", mem->memory);

//     return realsize;
// }

// int main() {
//     CURL *curl;
//     CURLcode res;
//     struct MemoryStruct chunk;
//     chunk.memory = malloc(1);
//     chunk.size = 0;

//     // libcurl 초기화
//     curl_global_init(CURL_GLOBAL_ALL);
//     curl = curl_easy_init();

//     if (curl) {
//         // API 요청 URL 생성
//         char api_url[256];
//         sprintf(api_url, "http://api.openweathermap.org/data/2.5/weather?id=%s&appid=%s&lang=en", CITY_ID, API_KEY);

//         curl_easy_setopt(curl, CURLOPT_URL, api_url);
//         curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
//         curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

//         // API 요청 실행
//         res = curl_easy_perform(curl);
//         if (res != CURLE_OK) {
//             fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
//         } else {
//             // JSON 파싱
//             json_error_t error;
//             json_t *root = json_loads(chunk.memory, 0, &error);

//             if (!root) {
//                 fprintf(stderr, "JSON 파싱 실패: %s\n", error.text);
//             } else {
//                 // 날씨 데이터 추출
//                 json_t *weather_array = json_object_get(root, "weather");
//                 if (json_is_array(weather_array)) {
//                     size_t array_size = json_array_size(weather_array);
//                     for (size_t i = 0; i < array_size; i++) {
//                         json_t *weather_obj = json_array_get(weather_array, i);
//                         if (json_is_object(weather_obj)) {
//                             // 날씨 ID, 주요 정보, 설명, 아이콘 ID 추출
//                             json_t *id = json_object_get(weather_obj, "id");
//                             json_t *main = json_object_get(weather_obj, "main");
//                             json_t *description = json_object_get(weather_obj, "description");
//                             json_t *icon = json_object_get(weather_obj, "icon");

//                             // 추출된 데이터 출력
//                             if (json_is_integer(id) && json_is_string(main) && json_is_string(description) && json_is_string(icon)) {
//                                 printf("날씨 ID: %lld\n", json_integer_value(id));
//                                 printf("주요 정보: %s\n", json_string_value(main));
//                                 printf("날씨 설명: %s\n", json_string_value(description));
//                                 printf("아이콘 ID: %s\n", json_string_value(icon));
//                             }
//                         }
//                     }
//                 }
//                 json_decref(root);
//             }
//         }
//         curl_easy_cleanup(curl);
//     }
//     free(chunk.memory);
//     curl_global_cleanup();
//     return 0;
// }




// // https://velog.io/@smh0116/OpenWeatherMap-%EB%82%A0%EC%94%A8-API-%EC%82%AC%EC%9A%A9%ED%95%B4%EB%B3%B4%EA%B8%B0
// // https://openweathermap.org/price
// // https://openweathermap.org/appid
// // https://openweathermap.org/current#example_JSON
// // https://home.openweathermap.org/api_keys