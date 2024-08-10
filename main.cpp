#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Archivo{
    string name;
};

struct Directorio{
    string name;
    vector<Archivo> archivos;
    vector<Directorio> subdirectorio;
};

bool findfile(Directorio& dir, string& path, string& target) {
    // Caso Base (detiene la recursividad)
    for(auto arch: dir.archivos){
        if(arch.name == target){
            path += "/" + dir.name;
            return true;
        }
    }

    for(auto subdir: dir.subdirectorio) {
        string subdirpath = path + "/" + dir.name;
        if(findfile(subdir,subdirpath,target)){
            path = subdirpath;
            return true;
        }
    }

    return false;
}

int main() {

    Directorio sistemaDeArchivos = {
            "root",
            {
                    {"archivo1.txt"},
                    {"archivo2.txt"}
            },
            {
                    {
                            "subdir1",
                            {
                                    {"archivo3.txt"},
                            },
                            {
                                    {
                                            "subdir2",
                                            {
                                                    {"target.txt"},
                                                    {"archivo4.txt"}
                                            },
                                            {}
                                    }
                            }
                    },
                    {"archivo5.txt"}
            }
    };

    string target = "target.txt";
    string path = "";

    if (findfile(sistemaDeArchivos, path, target)){
        cout << endl << "Archivo encontrado en " << path << "/" << target << endl;
    } else {
        cout << "Archivo no encontrado." << endl;
    }

    return 0;
}
