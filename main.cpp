#include <cpr/cpr.h>
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv) {
    cpr::Response r = cpr::Get(cpr::Url{"https://www.google.com/"},
                      cpr::Authentication{"user", "pass", cpr::AuthMode::BASIC},
                      cpr::Parameters{{"anon", "true"}, {"key", "value"}});
    std::cout << "Obtendo dados de https://www.google.com/..." << "\n\n";
    std::cout << "Status code: " << r.status_code << "\n\n";
    std::cout << "Resposta: " << "\n\n";
    std::cout << r.text << "\n";
    system("pause");
    return 0;
}
