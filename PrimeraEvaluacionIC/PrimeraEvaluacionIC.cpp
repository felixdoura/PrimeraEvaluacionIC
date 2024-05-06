#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// Struct del jugador
struct Player {
    string name;
    int health;
    int energy;
    int basicAttack;
    int defense;
};

// Struct para los enemigos (agregar mas caracteristicas?)
struct Enemy {
    string name;
    int health;
    int attack;
    int defense;
};

// Definicion del mapa. Tengo varias dudas de por que usar letras mayusculas para definir estas variables, en la documentacion que encontre lei que es por convencion.
// https://stackoverflow.com/questions/20269669/define-why-uppercase en este post tambien encontre por que usar un guion bajo como convencion. Preguntar en clase por este asunto.
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 5;

// Funcion para imprimir el mapa en la consola. Use la funcion vector que viene dada en el paquete vector. Documentacion de la funcion: https://cplusplus.com/reference/vector/vector/
void printMap(const vector<vector<char>>& map) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            cout << map[y][x] << " ";
        }
        cout << endl;
    }
}

// Funcion de la probabilidad de hacer un ataque efectivo
bool attackProbability(int probability) {
    int random = rand() % 100 + 1;
    // Lo que hago en la funcion es que el ataque se realice o no dependiendo de un numero aleatorio. Primero se elije un numero al azar de 1 al 100 y 
    // despues lo que pasa es que se compara el numero aleatorio con la probabilidad que el ataque sea eficaz. Todavia no lo decidi pero quizas haga que algun ataque o arma
    // Sea mas eficaz o eficiente que otra y capaz lo haga viendo el tipo de enemigo. (si pongo probability = 100 entonces el ataque va a pegar siempre)
    return random <= probability; 
}

// Funcion de batalla entre el jugador y un enemigo
void battle(Player& player, Enemy& enemy) {
    while (player.health > 0 && enemy.health > 0) {
        // Turno del jugador
        // Para este caso particular, puse que la probabilidad de que el jugador le acierte el ataque al enemigo sea de 80%
        if (attackProbability(80)) { 
            int damage = player.basicAttack - enemy.defense;
            // Haciendo pruebas agrego la siguiente linea para que en caso que el daño que le hago al enemigo no se vaya a numeros negativos.
            if (damage < 0) damage = 0;
            enemy.health -= damage;
            player.energy -= 2;
            cout << "Atacas al " << enemy.name << " y le haces " << damage << " puntos de vida.\n";
        }
        else {
            player.energy -= 2;
            cout << "Erraste el ataque.\n";
        }

        // Verificar si el enemigo ha sido derrotado
        if (enemy.health <= 0) {
            cout << " " << endl;
            cout << "Has derrotado al " << enemy.name << "!\n\n";
            cout << "Salud restante del jugador: " << player.health << endl;
            cout << "Energia restante del jugador: " << player.energy << "\n" << endl;
            break;
        }

        // Turno del enemigo
        // En el turno del enemigo hago lo mismo que con el turno del jugador, y para darle una ventaja el porcentaje de aciertos es bastante menor. Tambien agrego la linea
        // para evitar los puntos negativos.
        if (attackProbability(50)) { 
            int damage = enemy.attack - player.defense;
            if (damage < 0) damage = 0;
            player.health -= damage;
            cout << "El " << enemy.name << " te ataca y te inflige " << damage << " de vida.\n";
        }
        else {
            cout << "El ataque del " << enemy.name << " fallo.\n";
        }

        // Verificar si el jugador ha sido derrotado
        if (player.health <= 0) {
            cout << "Has sido derrotado por el " << enemy.name << "!\n";
            break;
        }
    }
}



int main()
{
    // randomizador
    srand(time(NULL));

    // El mapa se define como una matriz de caracteres (usando la funcion vector. documentacion mas arriba)
    vector<vector<char>> map(MAP_HEIGHT, vector<char>(MAP_WIDTH));

    // Inicializar mapa
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                // definicion de las paredes
                map[y][x] = 'X';
            }
            else {
                // definicion del piso
                map[y][x] = '.';
            }
        }
    }

    // Stats del jugador
    Player player;
    player.name = "Jugador";
    player.health = 100;
    player.energy = 100;
    player.basicAttack = 10;
    player.defense = 5;

    // Posicion del jugador en el mapa
    int playerX = 1;
    int playerY = 1;
    map[playerY][playerX] = 'P';

    // Contador de dias
    int days = 1;

    // Mensaje de bienvenida a la aventura, tengo que revisar si deberia poner algunas lineas mas.
    cout << "Bienvenido!\n";
    cout << "Como es tu nombre?: ";
    // cin >> player.name; --> hacer el input de esta forma genera un problema con el buffer de entrada de datos. segun lo que lei es mejor usar getline(cin, player.name);
    getline(cin, player.name);
    cout << "\n";

    cout << "Hola, " << player.name << "! Espero que estes listo para continuar, grandes desafios se avecinan.\n\n";

    cout << "-- Presiona cualquier tecla para continuar --";
    cin.get();
    system("cls");

    // La variable del enemigo Droide de combate tengo que declararla fuera del switch. Estuve intentando hacerlo en el case 1 pero me arrojaba un error. Poniendola aca funciona bien.
    Enemy combatDroid;

    while (true) {
        cout << "Estas en la base. Que deseas hacer?\n\n";
        cout << "1. Cazar Monstruos\n";
        cout << "2. Descansar\n";
        cout << "3. Salir del juego\n\n";
        cout << "Opcion: ";

        int opcion;
        cin >> opcion;

        // Limpiar el buffer de entrada. Segun lo que estuve leyendo con las siguientes funciones puedo ahorrarme varias lineas de codigo que tendria que definir yo para evitar
        // poner caracteres que no sirvan. Por ahora es la mejor forma que encontre para solucionar errores de input.
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
        case 1:
            cout << "\nEntras en la zona controlada por los droides!\n";
            combatDroid;
            combatDroid.name = "Droide de Combate";
            combatDroid.health = 50;
            combatDroid.attack = 10;
            combatDroid.defense = 5;
            battle(player, combatDroid);
            break;
        case 2:
            cout << "\nTe tomas un descanso!\n";
            player.health = 100;
            player.energy = 100;
            days++;
            cout << "Descansas durante la noche y te sientes renovado, recuperaste toda la vida y la energia para afrontar otro dia.\n";
            break;
        case 3:
            cout << "Hasta luego!\n";
            return 0;
        default:
            cout << "Opcion invalida. Por favor, selecciona una opcion valida.\n";
            break;
        }
    }

    return 0;
}


