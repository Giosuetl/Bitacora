#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>

const std::string FORMATO_COMPLETO = "%Y-%m-%d_%H-%M-%S";
const std::string FORMATO_HORA = "%H:%M.%S";
std::string fechas(bool soloHora)
{

    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    char buffer[80];


    if (soloHora)
    {
        std::strftime(buffer, sizeof(buffer), FORMATO_HORA.c_str(), &localTime);
        return  std::string(buffer);
    }
    
    std::strftime(buffer, sizeof(buffer), FORMATO_COMPLETO.c_str(), &localTime);
    return  std::string(buffer) + ".txt";
    
}
struct Bitacora
{
    std::string title;
    std::vector<std::string> entries;

    explicit Bitacora(const std::string& title)
        : title{ title }
    {
    }

    void add(const std::string& entry);

};

void Bitacora::add(const std::string& entry)
{
    entries.emplace_back(fechas(1) + ": " + entry);//para construir la cadena directamente en el vector sin necesidad de una copia adicional.
}


struct PersistenceManager
{
    static void save(const Bitacora& j, const std::string& filename)
    {
        std::ofstream ofs(filename);
        for (auto& s : j.entries)
            ofs << s << std::endl;
    }
};

int main()
{

    Bitacora bitacora{ "Dear Diary" };
    bitacora.add("El avion despego");
    bitacora.add("El avion vuela correctamente");

    bitacora.add("El avion aterrizo sin problemas");

    PersistenceManager pm;
    pm.save(bitacora, fechas(0));

    return 0;
}