#include "sistema.h"
#include "recursos.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

// Constructor
Sistema::Sistema() : usuarioActual(nullptr), reproduciendo(false),
    cancionesReproducidas(0), ultimoAnuncioMostrado(-1) {
    srand(time(nullptr));

    usuarios = new Usuario*[10];
    capacidadUsuarios = 10;
    numUsuarios = 0;

    artistas = new Artista*[20];
    capacidadArtistas = 20;
    numArtistas = 0;

    anuncios = new Anuncio*[50];
    capacidadAnuncios = 50;
    numAnuncios = 0;

    Recursos::inicializar();
}

// Destructor
Sistema::~Sistema() {
    liberarMemoria();
}

void Sistema::liberarMemoria() {
    for(int i = 0; i < numUsuarios; i++) {
        delete usuarios[i];
    }
    delete[] usuarios;

    for(int i = 0; i < numArtistas; i++) {
        delete artistas[i];
    }
    delete[] artistas;

    for(int i = 0; i < numAnuncios; i++) {
        delete anuncios[i];
    }
    delete[] anuncios;
}

// Expandir arrays
void Sistema::expandirUsuarios() {
    int nuevaCapacidad = capacidadUsuarios * 2;
    Usuario** nuevo = new Usuario*[nuevaCapacidad];
    for(int i = 0; i < numUsuarios; i++) {
        nuevo[i] = usuarios[i];
        Recursos::incrementarIteraciones();
    }
    delete[] usuarios;
    usuarios = nuevo;
    capacidadUsuarios = nuevaCapacidad;
}

void Sistema::expandirArtistas() {
    int nuevaCapacidad = capacidadArtistas * 2;
    Artista** nuevo = new Artista*[nuevaCapacidad];
    for(int i = 0; i < numArtistas; i++) {
        nuevo[i] = artistas[i];
        Recursos::incrementarIteraciones();
    }
    delete[] artistas;
    artistas = nuevo;
    capacidadArtistas = nuevaCapacidad;
}

void Sistema::expandirAnuncios() {
    int nuevaCapacidad = capacidadAnuncios * 2;
    Anuncio** nuevo = new Anuncio*[nuevaCapacidad];
    for(int i = 0; i < numAnuncios; i++) {
        nuevo[i] = anuncios[i];
        Recursos::incrementarIteraciones();
    }
    delete[] anuncios;
    anuncios = nuevo;
    capacidadAnuncios = nuevaCapacidad;
}

// Cargar datos
void Sistema::cargarDatos() {
    cout << "Cargando datos del sistema...\n";
    cargarUsuarios();
    cargarArtistas();
    cargarAnuncios();
    cout << "Datos cargados exitosamente.\n\n";
}




// Gestion de usuarios
Usuario* Sistema::buscarUsuario(const string& nickname) {
    for(int i = 0; i < numUsuarios; i++) {
        Recursos::incrementarIteraciones();
        if(usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}

bool Sistema::iniciarSesion(const string& nickname, const string& password) {
    Usuario* usuario = buscarUsuario(nickname);
    Recursos::incrementarIteraciones();

    if(usuario != nullptr && usuario->verificarPassword(password)) {
        usuarioActual = usuario;
        cout << "\n¡Bienvenido " << nickname << "!\n";
        usuarioActual->mostrarInfo();
        return true;
    }

    cout << "\nUsuario o contraseña incorrectos.\n";
    return false;
}

void Sistema::cerrarSesion() {
    if(usuarioActual != nullptr) {
        cout << "\nCerrando sesion de " << usuarioActual->getNickname() << "...\n";
        usuarioActual = nullptr;
    }
}

Usuario* Sistema::getUsuarioActual() {
    return usuarioActual;
}

// Gestion artistas
Artista* Sistema::buscarArtista(int id) {
    for(int i = 0; i < numArtistas; i++) {
        Recursos::incrementarIteraciones();
        if(artistas[i]->getId() == id) {
            return artistas[i];
        }
    }
    return nullptr;
}

Cancion* Sistema::buscarCancion(int idCancion) {
    int idArtista = idCancion / 10000;
    Artista* artista = buscarArtista(idArtista);
    Recursos::incrementarIteraciones();

    if(artista != nullptr) {
        return artista->buscarCancionPorId(idCancion);
    }
    return nullptr;
}

// Reproduccion aleatoria
void Sistema::reproduccionAleatoria() {
    if(usuarioActual == nullptr) {
        cout << "Debe iniciar sesion primero.\n";
        return;
    }

    Recursos::resetear();
    cout << "\n╔═════════════════════════════════════════════╗\n";
    cout << "║        REPRODUCCION ALEATORIA               ║\n";
    cout << "╚═════════════════════════════════════════════╝\n\n";

    // Recopilar todas las canciones
    int totalCanciones = 0;
    for(int i = 0; i < numArtistas; i++) {
        for(int j = 0; j < artistas[i]->getNumAlbumes(); j++) {
            Album* album = artistas[i]->getAlbum(j);
            totalCanciones += album->getNumCanciones();
            Recursos::incrementarIteraciones();
        }
    }

    if(totalCanciones == 0) {
        cout << "No hay canciones disponibles.\n";
        return;
    }

    cout << "Total de canciones en plataforma: " << totalCanciones << "\n";
    cout << "Reproduciendo " << (usuarioActual->esPremium() ? "sin" : "con") << " publicidad\n";
    cout << "Calidad: " << usuarioActual->getBitrate() << " kbps\n\n";

    int K = 5; // Reproducir 5 canciones
    cancionesReproducidas = 0;

    for(int reproduccion = 0; reproduccion < K; reproduccion++) {
        // Seleccionar cancion aleatoria
        int indiceAleatorio = generarAleatorio(0, totalCanciones - 1);
        int contador = 0;
        Cancion* cancionActual = nullptr;
        Album* albumActual = nullptr;

        for(int i = 0; i < numArtistas && cancionActual == nullptr; i++) {
            for(int j = 0; j < artistas[i]->getNumAlbumes() && cancionActual == nullptr; j++) {
                Album* album = artistas[i]->getAlbum(j);
                for(int k = 0; k < album->getNumCanciones(); k++) {
                    if(contador == indiceAleatorio) {
                        cancionActual = album->getCancion(k);
                        albumActual = album;
                        break;
                    }
                    contador++;
                    Recursos::incrementarIteraciones();
                }
            }
        }

        if(cancionActual != nullptr) {
            cout << "\n♪ Reproduciendo (" << (reproduccion+1) << "/" << K << "):\n";
            cout << "   Cancion: " << cancionActual->getNombre() << "\n";
            cout << "   Album: " << albumActual->getNombre() << "\n";
            cout << "   Duracion: " << cancionActual->getDuracion()/60
                      << ":" << (cancionActual->getDuracion()%60 < 10 ? "0" : "")
                      << cancionActual->getDuracion()%60 << "\n";
            cout << "   Audio: " << cancionActual->getRutaAudio(usuarioActual->getBitrate()) << "\n";
            cout << "   Portada: " << albumActual->getRutaPortada() << "\n";

            cancionActual->incrementarReproducciones();
            cancionesReproducidas++;

            // Mostrar anuncio cada 2 canciones (usuarios estandar)
            if(!usuarioActual->esPremium() && cancionesReproducidas % 2 == 0) {
                pausa(1);
                mostrarAnuncio();
                pausa(2);
            }

            // Simular reproduccion (3 segundos)
            cout << "   [Reproduciendo...";
            cout.flush();
            pausa(3);
            cout << " ✓]\n";
        }
    }

    cout << "\n¡Reproduccion finalizada!\n";
    size_t memoriaTotal = calcularMemoriaTotal();
    Recursos::mostrarMetricas(memoriaTotal);
}

// Mostrar anuncio
void Sistema::mostrarAnuncio() {
    Anuncio* anuncio = seleccionarAnuncioPorPrioridad();
    if(anuncio != nullptr) {
        anuncio->mostrar();
    }
}

Anuncio* Sistema::seleccionarAnuncioPorPrioridad() {
    if(numAnuncios == 0) return nullptr;

    // Calcular suma total de prioridades
    int sumaPrioridades = 0;
    for(int i = 0; i < numAnuncios; i++) {
        sumaPrioridades += anuncios[i]->getPrioridad();
        Recursos::incrementarIteraciones();
    }

    // Generar numero aleatorio
    int aleatorio = generarAleatorio(1, sumaPrioridades);
    int acumulado = 0;

    // Seleccionar anuncio
    for(int i = 0; i < numAnuncios; i++) {
        acumulado += anuncios[i]->getPrioridad();
        if(aleatorio <= acumulado && i != ultimoAnuncioMostrado) {
            ultimoAnuncioMostrado = i;
            Recursos::incrementarIteraciones();
            return anuncios[i];
        }
        Recursos::incrementarIteraciones();
    }

    // Si no encontro, devolver uno diferente al ultimo
    int idx = (ultimoAnuncioMostrado + 1) % numAnuncios;
    ultimoAnuncioMostrado = idx;
    return anuncios[idx];
}

// Menu favoritos
void Sistema::menuFavoritos() {
    if(usuarioActual == nullptr || !usuarioActual->esPremium()) {
        cout << "\nEsta funcionalidad es exclusiva para usuarios Premium.\n";
        return;
    }

    int opcion = 0;
    do {
        cout << "\n╔═══════════════════════════════════════════╗\n";
        cout << "║         MI LISTA DE FAVORITOS            ║\n";
        cout << "╠═══════════════════════════════════════════╣\n";
        cout << "║ 1. Editar mi lista de favoritos          ║\n";
        cout << "║ 2. Seguir otra lista de favoritos        ║\n";
        cout << "║ 3. Ejecutar mi lista de favoritos        ║\n";
        cout << "║ 4. Volver al menu principal              ║\n";
        cout << "╚═══════════════════════════════════════════╝\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1:
            editarFavoritos();
            break;
        case 2:
            seguirOtraLista();
            break;
        case 3:
            ejecutarFavoritos();
            break;
        case 4:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion invalida.\n";
        }
        Recursos::incrementarIteraciones();
    } while(opcion != 4);
}

void Sistema::editarFavoritos() {
    Recursos::resetear();

    int opcion = 0;
    do {
        Playlist* favoritos = usuarioActual->getListaFavoritos();
        if(favoritos != nullptr) {
            favoritos->mostrarInfo();
        }

        cout << "\n1. Agregar cancion\n";
        cout << "2. Eliminar cancion\n";
        cout << "3. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(opcion == 1) {
            listarArtistas();
            cout << "Ingrese ID de la cancion (9 digitos): ";
            int idCancion;
            cin >> idCancion;

            Cancion* cancion = buscarCancion(idCancion);
            if(cancion != nullptr) {
                cancion->mostrarInfo();
                if(usuarioActual->agregarFavorito(idCancion)) {
                    cout << "✓ Cancion agregada a favoritos.\n";
                } else {
                    cout << "✗ La cancion ya esta en favoritos.\n";
                }
            } else {
                cout << "Cancion no encontrada.\n";
            }
        } else if(opcion == 2) {
            cout << "Ingrese ID de la cancion a eliminar: ";
            int idCancion;
            cin >> idCancion;

            if(usuarioActual->eliminarFavorito(idCancion)) {
                cout << "✓ Cancion eliminada de favoritos.\n";
            } else {
                cout << "✗ La cancion no esta en favoritos.\n";
            }
        }
        Recursos::incrementarIteraciones();
    } while(opcion != 3);

    size_t memoriaTotal = calcularMemoriaTotal();
    Recursos::mostrarMetricas(memoriaTotal);
}

void Sistema::seguirOtraLista() {
    Recursos::resetear();

    cout << "\nIngrese el nickname del usuario a seguir: ";
    string nicknameASeguir;
    cin >> nicknameASeguir;

    Usuario* otroUsuario = buscarUsuario(nicknameASeguir);

    if(otroUsuario == nullptr) {
        cout << "Usuario no encontrado.\n";
    } else if(!otroUsuario->esPremium()) {
        cout << "El usuario no es Premium (no tiene lista de favoritos).\n";
    } else if(otroUsuario == usuarioActual) {
        cout << "No puedes seguir tu propia lista.\n";
    } else {
        Playlist* otraLista = otroUsuario->getListaFavoritos();
        if(otraLista != nullptr) {
            usuarioActual->seguirListaFavoritos(*otraLista);
            cout << "✓ Lista de favoritos fusionada exitosamente.\n";
            cout << "Canciones agregadas: " << otraLista->getNumCanciones() << "\n";
        }
    }

    size_t memoriaTotal = calcularMemoriaTotal();
    Recursos::mostrarMetricas(memoriaTotal);
}

void Sistema::ejecutarFavoritos() {
    Recursos::resetear();

    Playlist* favoritos = usuarioActual->getListaFavoritos();
    if(favoritos == nullptr || favoritos->getNumCanciones() == 0) {
        cout << "Tu lista de favoritos esta vacia.\n";
        return;
    }

    cout << "\n¿Reproducir en orden original (1) o aleatorio (2)? ";
    int modoReproduccion;
    cin >> modoReproduccion;

    bool aleatorio = (modoReproduccion == 2);

    cout << "\n╔═══════════════════════════════════════════╗\n";
    cout << "║      REPRODUCIENDO MIS FAVORITOS         ║\n";
    cout << "╚═══════════════════════════════════════════╝\n\n";

    int numCanciones = favoritos->getNumCanciones();
    int cancionesAReproducir = (numCanciones < 5) ? numCanciones : 5;

    for(int i = 0; i < cancionesAReproducir; i++) {
        int indice = aleatorio ? generarAleatorio(0, numCanciones - 1) : i;
        int idCancion = favoritos->getIdCancion(indice);

        Cancion* cancion = buscarCancion(idCancion);
        if(cancion != nullptr) {
            // Buscar album
            Album* album = nullptr;
            for(int j = 0; j < numArtistas && album == nullptr; j++) {
                for(int k = 0; k < artistas[j]->getNumAlbumes(); k++) {
                    if(artistas[j]->getAlbum(k)->buscarCancionPorId(idCancion) != nullptr) {
                        album = artistas[j]->getAlbum(k);
                        break;
                    }
                    Recursos::incrementarIteraciones();
                }
            }

            cout << "\n♪ Reproduciendo (" << (i+1) << "/" << cancionesAReproducir << "):\n";
            cout << "   " << cancion->getNombre() << "\n";
            if(album != nullptr) {
                cout << "   Album: " << album->getNombre() << "\n";
                cout << "   Portada: " << album->getRutaPortada() << "\n";
            }
            cout << "   Audio: " << cancion->getRutaAudio(320) << "\n";

            cout << "   [Reproduciendo...";
            cout.flush();
            pausa(3);
            cout << " ✓]\n";
        }
        Recursos::incrementarIteraciones();
    }

    cout << "\n¡Reproduccion finalizada!\n";
    size_t memoriaTotal = calcularMemoriaTotal();
    Recursos::mostrarMetricas(memoriaTotal);
}

void Sistema::listarArtistas() const {
    std::cout << "\n═══════════════════════════════════════\n";
    std::cout << "         ARTISTAS DISPONIBLES\n";
    std::cout << "═══════════════════════════════════════\n";

    for(int i = 0; i < numArtistas; i++) {
        std::cout << (i+1) << ". " << artistas[i]->getNombre()
        << " (" << artistas[i]->getTotalCanciones() << " canciones)\n";
        Recursos::incrementarIteraciones();
    }
    std::cout << "\n";
}

// Menu principal
void Sistema::mostrarMenuPrincipal() {
    if(usuarioActual == nullptr) return;

    cout << "\n╔═══════════════════════════════════════════════════╗\n";
    cout << "║              UdeATunes - Menu Principal          ║\n";
    cout << "╠═══════════════════════════════════════════════════╣\n";
    cout << "║ Usuario: " << usuarioActual->getNickname()
              << " [" << usuarioActual->getMembresiaStr() << "]" << "\n";
    cout << "╠═══════════════════════════════════════════════════╣\n";
    cout << "║ 1. Reproduccion aleatoria                        ║\n";

    if(usuarioActual->esPremium()) {
        cout << "║ 2. Mi lista de favoritos (Premium)              ║\n";
    }

    cout << "║ 3. Ver artistas disponibles                      ║\n";
    cout << "║ 4. Cerrar sesion                                 ║\n";
    cout << "╚═══════════════════════════════════════════════════╝\n";
    cout << "Seleccione opcion: ";
}

void Sistema::ejecutarMenuPrincipal() {
    int opcion = 0;

    do {
        mostrarMenuPrincipal();
        cin >> opcion;

        switch(opcion) {
        case 1:
            reproduccionAleatoria();
            break;
        case 2:
            if(usuarioActual->esPremium()) {
                menuFavoritos();
            } else {
                cout << "Opcion no disponible para usuarios estandar.\n";
            }
            break;
        case 3:
            listarArtistas();
            break;
        case 4:
            cerrarSesion();
            break;
        default:
            cout << "Opcion invalida.\n";
        }
        Recursos::incrementarIteraciones();

    } while(opcion != 4);
}

// Calcular memoria total
size_t Sistema::calcularMemoriaTotal() const {
    size_t total = sizeof(Sistema);

    // Memoria de usuarios
    total += capacidadUsuarios * sizeof(Usuario*);
    for(int i = 0; i < numUsuarios; i++) {
        total += usuarios[i]->calcularMemoria();
        Recursos::incrementarIteraciones();
    }

    // Memoria de artistas
    total += capacidadArtistas * sizeof(Artista*);
    for(int i = 0; i < numArtistas; i++) {
        total += artistas[i]->calcularMemoria();
        Recursos::incrementarIteraciones();
    }

    // Memoria de anuncios
    total += capacidadAnuncios * sizeof(Anuncio*);
    for(int i = 0; i < numAnuncios; i++) {
        total += anuncios[i]->calcularMemoria();
        Recursos::incrementarIteraciones();
    }

    return total;
}

// Funciones auxiliares
int Sistema::generarAleatorio(int min, int max) {
    return min + (rand() % (max - min + 1));
}

void Sistema::pausa(int segundos) {
    this_thread::sleep_for(chrono::seconds(segundos));
}

void Sistema::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


std::string Sistema::reemplazarGuionesBajos(const std::string& str) {
    std::string resultado = str;
    for(size_t i = 0; i < resultado.length(); i++) {
        if(resultado[i] == '_') {
            resultado[i] = ' ';
        }
    }
    return resultado;
}

void Sistema::saltarLineasComentario(std::ifstream& archivo) {
    std::string linea;
    while(archivo.peek() == '#' || archivo.peek() == '\n') {
        std::getline(archivo, linea);
    }
}

//CARGA DE USUARIOS

void Sistema::cargarUsuarios() {
    std::ifstream archivo("data/usuarios.txt");

    if(!archivo.is_open()) {
        std::cout << "Archivo usuarios.txt no encontrado. Creando usuarios de prueba...\n";
        // Fallback a usuarios hardcodeados
        if(numUsuarios >= capacidadUsuarios) expandirUsuarios();
        usuarios[numUsuarios++] = new Usuario("juan123", "1234", PREMIUM,
                                              "Medellin", "Colombia", "2024-01-15");

        if(numUsuarios >= capacidadUsuarios) expandirUsuarios();
        usuarios[numUsuarios++] = new Usuario("maria_s", "pass", ESTANDAR,
                                              "Bogota", "Colombia", "2024-03-20");

        if(numUsuarios >= capacidadUsuarios) expandirUsuarios();
        usuarios[numUsuarios++] = new Usuario("carlos.m", "abc123", PREMIUM,
                                              "Cali", "Colombia", "2024-02-10");
        return;
    }

    std::cout << "Cargando usuarios desde archivo...\n";

    std::string nickname, password, ciudad, pais, fecha;
    int membresia;

    saltarLineasComentario(archivo);

    while(archivo >> nickname >> password >> membresia >> ciudad >> pais >> fecha) {
        TipoMembresia tipo = (membresia == 1) ? PREMIUM : ESTANDAR;

        std::string ciudadFormateada = reemplazarGuionesBajos(ciudad);
        std::string paisFormateado = reemplazarGuionesBajos(pais);

        if(numUsuarios >= capacidadUsuarios) expandirUsuarios();
        usuarios[numUsuarios++] = new Usuario(nickname, password, tipo,
                                              ciudadFormateada, paisFormateado, fecha);

        Recursos::incrementarIteraciones();
    }

    archivo.close();
    std::cout << numUsuarios << " usuarios cargados.\n";
}

//ARTISTAS Y ALBUMS

void Sistema::cargarArtistas() {
    std::ifstream archivoArtistas("data/artistas.txt");
    std::ifstream archivoAlbumes("data/albumes.txt");
    std::ifstream archivoCanciones("data/canciones.txt");

    if(!archivoArtistas.is_open() || !archivoAlbumes.is_open() || !archivoCanciones.is_open()) {
        std::cout << "Archivos de música no encontrados. Creando datos de prueba...\n";
        cargarArtistasHardcoded(); // Función de respaldo
        return;
    }

    std::cout << "Cargando artistas desde archivo...\n";

    // === CARGAR ARTISTAS ===
    int id, edad, seguidores, posicion;
    std::string nombre, pais;

    saltarLineasComentario(archivoArtistas);

    while(archivoArtistas >> id >> nombre >> edad >> pais >> seguidores >> posicion) {
        std::string nombreFormateado = reemplazarGuionesBajos(nombre);
        std::string paisFormateado = reemplazarGuionesBajos(pais);

        Artista* artista = new Artista(id, nombreFormateado, edad, paisFormateado);
        artista->setSeguidores(seguidores);
        artista->setPosicionTendencias(posicion);

        if(numArtistas >= capacidadArtistas) expandirArtistas();
        artistas[numArtistas++] = artista;

        Recursos::incrementarIteraciones();
    }

    std::cout << numArtistas << " artistas cargados.\n";

    //CARGAR ALBUMES
    std::cout << "Cargando álbumes desde archivo...\n";

    int idArtista, idAlbum;
    std::string nombreAlbum, fecha, sello, generosStr;
    float puntuacion;

    saltarLineasComentario(archivoAlbumes);

    int totalAlbumes = 0;
    while(archivoAlbumes >> idArtista >> idAlbum >> nombreAlbum >> fecha >> sello >> puntuacion >> generosStr) {
        Artista* artista = buscarArtista(idArtista);

        if(artista != nullptr) {
            std::string nombreFormateado = reemplazarGuionesBajos(nombreAlbum);
            std::string selloFormateado = reemplazarGuionesBajos(sello);

            std::string rutaPortada = "/storage/" + nombreFormateado + "/image/" + nombreFormateado + ".png";

            Album* album = new Album(idAlbum, nombreFormateado, fecha, selloFormateado, rutaPortada);
            album->setPuntuacion(puntuacion);

            // Procesar géneros (separados por |)
            std::string genero = "";
            for(size_t i = 0; i < generosStr.length(); i++) {
                if(generosStr[i] == '|') {
                    album->agregarGenero(genero);
                    genero = "";
                } else {
                    genero += generosStr[i];
                }
            }
            if(genero.length() > 0) {
                album->agregarGenero(genero);
            }

            artista->agregarAlbum(album);
            totalAlbumes++;
        }

        Recursos::incrementarIteraciones();
    }

    std::cout << totalAlbumes << " álbumes cargados.\n";

    //CARGAR CANCIONES
    std::cout << "Cargando canciones desde archivo...\n";

    int idCancion, duracion;
    std::string nombreCancion, rutaBase;

    saltarLineasComentario(archivoCanciones);

    int totalCanciones = 0;
    while(archivoCanciones >> idCancion >> nombreCancion >> duracion >> rutaBase) {
        int idArtistaCancion = idCancion / 10000;
        int idAlbumCancion = (idCancion / 100) % 100;

        Artista* artista = buscarArtista(idArtistaCancion);

        if(artista != nullptr) {
            Album* album = artista->buscarAlbumPorId(idAlbumCancion);

            if(album != nullptr) {
                std::string nombreFormateado = reemplazarGuionesBajos(nombreCancion);

                Cancion* cancion = new Cancion(idCancion, nombreFormateado, duracion, rutaBase);

                // Agregar compositor genérico
                cancion->agregarCompositor(Credito("Compositor", "Generico", "GEN0000001", COMPOSITOR));

                album->agregarCancion(cancion);
                totalCanciones++;
            }
        }

        Recursos::incrementarIteraciones();
    }

    // Calcular duración total de álbumes
    for(int i = 0; i < numArtistas; i++) {
        for(int j = 0; j < artistas[i]->getNumAlbumes(); j++) {
            artistas[i]->getAlbum(j)->calcularDuracionTotal();
        }
    }

    archivoArtistas.close();
    archivoAlbumes.close();
    archivoCanciones.close();

    std::cout << totalCanciones << " canciones cargadas.\n";
}



void Sistema::cargarArtistasHardcoded() {
    // Tu código original hardcoded (como respaldo)
    Artista* artista1 = new Artista(10001, "Shakira", 47, "Colombia");
    artista1->setSeguidores(5000000);
    artista1->setPosicionTendencias(5);

    Album* album1 = new Album(1, "Pies Descalzos", "1995-10-06",
                              "Sony Music", "/storage/shakira/image/pies_descalzos.png");
    album1->agregarGenero("Pop");
    album1->agregarGenero("Latina");
    album1->setPuntuacion(8.5f);

    Cancion* c1 = new Cancion(1000101, "Estoy Aqui", 235,
                              "/storage/shakira/audio/estoy_aqui");
    c1->agregarCompositor(Credito("Shakira", "Ripoll", "COL1234567", COMPOSITOR));
    album1->agregarCancion(c1);

    Cancion* c2 = new Cancion(1000102, "Antologia", 270,
                              "/storage/shakira/audio/antologia");
    album1->agregarCancion(c2);

    album1->calcularDuracionTotal();
    artista1->agregarAlbum(album1);

    if(numArtistas >= capacidadArtistas) expandirArtistas();
    artistas[numArtistas++] = artista1;
}

// CARGA DE ANUNCIOS

void Sistema::cargarAnuncios() {
    std::ifstream archivo("data/anuncios.txt");

    if(!archivo.is_open()) {
        std::cout << "Archivo anuncios.txt no encontrado. Creando anuncios de prueba...\n";
        // Fallback
        if(numAnuncios >= capacidadAnuncios) expandirAnuncios();
        anuncios[numAnuncios++] = new Anuncio(1,
                                              "Coca-Cola: Destapa la felicidad.", AAA);

        if(numAnuncios >= capacidadAnuncios) expandirAnuncios();
        anuncios[numAnuncios++] = new Anuncio(2,
                                              "Nike: Just Do It.", B);
        return;
    }

    std::cout << "Cargando anuncios desde archivo...\n";

    int id, categoria;
    std::string lineaCompleta, mensaje;

    saltarLineasComentario(archivo);

    while(archivo >> id >> categoria) {
        // Leer el resto de la línea como mensaje
        std::getline(archivo, mensaje);

        // Eliminar espacio inicial
        if(mensaje.length() > 0 && mensaje[0] == ' ') {
            mensaje = mensaje.substr(1);
        }

        CategoriaAnuncio cat;
        switch(categoria) {
        case 0: cat = C; break;
        case 1: cat = B; break;
        case 2: cat = AAA; break;
        default: cat = C;
        }

        if(numAnuncios >= capacidadAnuncios) expandirAnuncios();
        anuncios[numAnuncios++] = new Anuncio(id, mensaje, cat);

        Recursos::incrementarIteraciones();
    }

    archivo.close();
    std::cout << numAnuncios << " anuncios cargados.\n";
}

//GUARDAR DATOS

void Sistema::guardarDatos() {
    std::cout << "\nGuardando datos del sistema...\n";

    // Guardar favoritos de usuarios premium
    std::ofstream archivo("favoritos.txt");
    if(archivo.is_open()) {
        for(int i = 0; i < numUsuarios; i++) {
            if(usuarios[i]->esPremium()) {
                Playlist* favoritos = usuarios[i]->getListaFavoritos();
                if(favoritos != nullptr && favoritos->getNumCanciones() > 0) {
                    archivo << usuarios[i]->getNickname() << " "
                            << favoritos->getNumCanciones() << "\n";

                    for(int j = 0; j < favoritos->getNumCanciones(); j++) {
                        archivo << favoritos->getIdCancion(j) << "\n";
                    }
                }
            }
        }
        archivo.close();
        std::cout << "Favoritos guardados.\n";
    }

    std::cout << "Datos guardados exitosamente.\n";
}
