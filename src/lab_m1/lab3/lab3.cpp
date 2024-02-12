#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>
#include <string>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;

typedef struct coords{
    float x, y;
}coords;

typedef struct forme{
    glm::mat3 modelMatrix;
    Mesh* mesh;
    coords coord;
    coords scale;
    glm::vec3 color;
    char culoare[10];
    bool on;
}forme;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init() {
    // declarare de variabile
    glm::ivec2 resolution; 
    auto camera = GetSceneCamera();
    float squareSide; 
    coords center, scale, translate;
    glm::vec3 corner;

    // initializare de variabile
    // scena
    resolution = window->GetResolution();
    window->SetSize(1280, 720);
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.02f, 100);
    camera->SetPosition(glm::vec3(0, 0, 10));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    corner = glm::vec3(0,0,0);
    squareSide = 100; 
    center.x = squareSide / 2;
    center.y = squareSide / 2;
    translate.x = 2300;
    translate.y = 2300;
    scale.x = 1;
    scale.y = 1;
    angularStep = 0;

    // creare fiecare forma in parte
    // tabla de joc - elemente statice
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0), true);
    AddMeshToList(square1);
    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);
    Mesh* squaree = object2D::CreateSquare("squaree", corner, squareSide, glm::vec3(1, 1, 1), false);
    AddMeshToList(squaree);
    Mesh* star = object2D::CreateStar("star", corner, squareSide, glm::vec3(1, 0, 1), true);
    AddMeshToList(star);
    Mesh* point = object2D::CreateStar("point", corner, squareSide / 2, glm::vec3(1, 1, 1), true);
    AddMeshToList(point);

    // tabla de joc - elemente dinamice
    // elemente jucatori
    Mesh* diamond1 = object2D::CreateDiamond("diamond1", corner, squareSide, glm::vec3(1, 0.5f, 0), true);
    AddMeshToList(diamond1);
    Mesh* diamond2 = object2D::CreateDiamond("diamond2", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(diamond2);
    Mesh* diamond3 = object2D::CreateDiamond("diamond3", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(diamond3);
    Mesh* diamond4 = object2D::CreateDiamond("diamond4", corner, squareSide, glm::vec3(0.5f, 0, 1), true);
    AddMeshToList(diamond4);
    // vieti
    Mesh* heart = object2D::CreateHeart("heart", corner, squareSide / 2, glm::vec3(1, 0, 0), true);
    AddMeshToList(heart);
    Mesh* dead = object2D::CreateHeart("dead", corner, squareSide / 2, glm::vec3(0, 0, 0), true);
    AddMeshToList(dead);
    // proiectile
    Mesh* pr1 = object2D::CreateStar("pr1", corner, squareSide, glm::vec3(1, 0.5f, 0), true);
    AddMeshToList(pr1);
    Mesh* pr2 = object2D::CreateStar("pr2", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(pr2);
    Mesh* pr3 = object2D::CreateStar("pr3", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(pr3);
    Mesh* pr4 = object2D::CreateStar("pr4", corner, squareSide, glm::vec3(0.5f, 0, 1), true);
    AddMeshToList(pr4);
    // inamici / hexagoane
    Mesh* hexagone1 = object2D::CreateHexa("hexagone1", corner, squareSide, glm::vec3(1, 0.5f, 0), true);
    AddMeshToList(hexagone1);
    Mesh* hexagone2 = object2D::CreateHexa("hexagone2", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(hexagone2);
    Mesh* hexagone3 = object2D::CreateHexa("hexagone3", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(hexagone3);
    Mesh* hexagone4 = object2D::CreateHexa("hexagone4", corner, squareSide, glm::vec3(0.5f, 0, 1), true);
    AddMeshToList(hexagone4);
}

forme forma;
forme forma2;
// date predefinite, un fel de default in functie de fereastra 
// bine, la mine fereastra e o dimensiune standard
coords star;
coords hexa_coords; // si asta cred ca se patreaza
vector<forme> squares, hexa, dias, lives, stars, cadrane, dia1_pts, dia2_pts, dia3_pts, dia4_pts, pts, prs; // si pe aici folosesc din variabile
int nr = 0;
vector<bool> create_dia, create_dias;
bool okok;
vector<coords> hexas = {{2300, 100}, {2300, 300}, {2300, 500}, {2300, 2000}};
vector<coords> cadrane_map = {{12, 141}, {88, 66}, {113, 141}, {188, 66}, {213, 141}, {287, 66}, {312, 141}, {388, 66}};
vector<coords> squares_map = {{100, 704}, {175, 629}, {200, 704}, {275, 629}, {300, 704}, {375, 629}, 
{100, 604}, {175, 529}, {200, 604}, {275, 529}, {300, 604}, {375, 529},
{100, 504}, {175, 429}, {200, 504}, {275, 429}, {300, 504}, {375, 429}};
forme rectangle;
int remainingLives = 3;
float currentTime = 0;
int selected = -1;
int aici;
coords temporaryRombPosition = {-200, -200}; 
bool hold = false;
int stele = 5;
bool odata = true;
int aci;

void Lab3::FrameStart()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // declarare de variabile
    glm::ivec2 resolution; 
    
    // initializare de variabile
    resolution = window->GetResolution();
   
    glViewport(0, 0, resolution.x, resolution.y);
}

void Lab3::Update(float deltaTimeSeconds) {
    // declarare de variabile
    glm::ivec2 resolution; 
    float squareSide; 
    glm::vec3 corner;
    coords coordonate;

    // initializare de variabile
    resolution = window->GetResolution();
    squareSide = 100; 
    corner = glm::vec3(0,0,0);

    // incep cu tabla de joc, mai exact cu dreptunghiul rosu
    coordonate.y = 35;
    coordonate.x = 25;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    rectangle.scale = {1.0f, 1.0f};
    rectangle.coord = coordonate;
    rectangle.color = glm::vec3(0,1,0);
    rectangle.on = true;
    strcpy(rectangle.culoare, "rosu");
    rectangle.mesh = meshes["rectangle"];
    rectangle.modelMatrix = modelMatrix;
    RenderMesh2D(rectangle.mesh, shaders["VertexColor"], rectangle.modelMatrix);

    coordonate.y = 35;
    for (int i = 0; i < 3; i++) {
        coordonate.x = 200;
        for (int j = 0; j < 3; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
            forma.scale = {1.0f, 1.0f};
            forma.coord = coordonate;
            forma.color = glm::vec3(0,1,0);
            strcpy(forma.culoare, "verde");
            forma.mesh = meshes["square1"];
            forma.modelMatrix = modelMatrix;
            forma.on = true;
            squares.push_back(forma);
            RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
            coordonate.x = coordonate.x + 200;
        }
        coordonate.y = coordonate.y + 200;
    }

    // trec la cadrane diamante
    coordonate.x = 25;
    coordonate.y = window->GetResolution().y / 3 + 200;
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.color = glm::vec3(1,1,1);
        strcpy(forma.culoare, "alb");
        forma.mesh = meshes["squaree"];
        forma.scale = {1.0f, 1.0f};
        forma.coord = coordonate;
        forma.modelMatrix = modelMatrix;
        forma.on = true; 
        cadrane.push_back(forma);
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
        coordonate.x = coordonate.x + 200;
    }  

    // stiu ca sunt cam hardcodate, dar am pus elementele statice ochiometric. 
    // ma rog, si la initializarea coordonatelor elemenetelor dinamice am cautat niste valori initiale, 
    // dar apoi se randomizeaza sau se face prin pasare de buton mouse
         
    // aici sunt tipurile de romburi incadrate in cadrane
    // aka primele patru elemente din vectorul de romburi sau diamante cum le mai numesc eu
    // deci dias sunt toate diamantele. diamantele pe culori vor fi vectori gen dias1, dias2, dias3, dias4
    coordonate.x = 75;
    coordonate.y = window->GetResolution().y / 3 + 275;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    strcpy(forma.culoare, "portocaliu");
    forma.color = glm::vec3(1, 0.5f, 0);
    forma.mesh = meshes["diamond1"];
    forma.scale = {1.0f, 1.0f};
    forma.coord = coordonate;
    forma.on = true;
    forma.modelMatrix = modelMatrix;
    RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    okok = false;
    create_dia.push_back(okok);

    coordonate.x += 200;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    forma.color = glm::vec3(0, 0, 1);
    strcpy(forma.culoare, "albastru");
    forma.mesh = meshes["diamond2"];
    forma.scale = {1.0f, 1.0f};
    forma.coord = coordonate;
    forma.on = true;
    forma.modelMatrix = modelMatrix;
    RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    okok = false;
    create_dia.push_back(okok);

    coordonate.x += 200;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    forma.color = glm::vec3(1, 1, 0);
    strcpy(forma.culoare, "galben");
    forma.mesh = meshes["diamond3"];
    forma.on = true;
    forma.scale = {1.0f, 1.0f};
    forma.coord = coordonate;
    forma.modelMatrix = modelMatrix;
    RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    okok = false;
    create_dia.push_back(okok);

    coordonate.x += 200;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    forma.color = glm::vec3(0.5, 0, 1);
    strcpy(forma.culoare, "mov");
    forma.mesh = meshes["diamond4"];
    forma.on = true;
    forma.scale = {1.0f, 1.0f};
    forma.coord = coordonate;
    forma.modelMatrix = modelMatrix;
    RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    okok = false;
    create_dia.push_back(okok);

    for (int i = 0; i < squares.size(); i++) {
        okok = false;
        create_dias.push_back(okok);
    }

    // aici sunt grupele de puncte pentru fiecare romb
    // astea nu le mai pun in vreun vector ca nu le misc sau selected, sunt statice
    // bine, chiar daca erau statice patratele, tot le am pus in vectori
    coordonate.x = 100;
    coordonate.y = window->GetResolution().y / 3 + 160;
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
    forma.color = glm::vec3(1, 1, 1);
    strcpy(forma.culoare, "alb");
    forma.mesh = meshes["point"];
    forma.on = true;
    forma.scale = {1.0f, 1.0f};
    forma.coord = coordonate;
    forma.modelMatrix = modelMatrix;
    dia1_pts.push_back(forma);
    RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);

    coordonate.x = 275;
    coordonate.y = window->GetResolution().y / 3 + 160;
    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.color = glm::vec3(1, 1, 1);
        strcpy(forma.culoare, "alb");
        forma.mesh = meshes["point"];
        forma.on = true;
        forma.scale = {1.0f, 1.0f};
        forma.coord = coordonate;
        forma.modelMatrix = modelMatrix;
        dia2_pts.push_back(forma);
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
        coordonate.x += 50;
    }
    
    coordonate.x = 475;
    coordonate.y = window->GetResolution().y / 3 + 160;
    for (int i = 0; i < 2; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.color = glm::vec3(1, 1, 1);
        strcpy(forma.culoare, "alb");
        forma.mesh = meshes["point"];
        forma.on = true;
        forma.scale = {1.0f, 1.0f};
        forma.coord = coordonate;
        forma.modelMatrix = modelMatrix;
        dia3_pts.push_back(forma);
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
        coordonate.x += 50;
    }

    coordonate.x = 650;
    coordonate.y = window->GetResolution().y / 3 + 160;
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.color = glm::vec3(1, 1, 1);
        strcpy(forma.culoare, "alb");
        forma.mesh = meshes["point"];
        forma.on = true;
        forma.scale = {1.0f, 1.0f};
        forma.coord = coordonate;
        forma.modelMatrix = modelMatrix;
        dia4_pts.push_back(forma);
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
        coordonate.x += 50;
    }

    // aici sunt punctele pentru a pune diamante
    coordonate.x = 925;
    coordonate.y = window->GetResolution().y / 3 + 175;
    for (int i = 0; i < 1000; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.color = glm::vec3(1, 1, 1);
        strcpy(forma.culoare, "alb");
        forma.mesh = meshes["point"];
        forma.on = true;
        forma.coord = coordonate;
        forma.scale = {1.0f, 1.0f};
        forma.modelMatrix = modelMatrix;
        pts.push_back(forma);
        coordonate.x += 50;
    }
   
    for (int i = 0; i < stele; i++) {            
        RenderMesh2D(pts[i].mesh, shaders["VertexColor"],pts[i].modelMatrix);
    }

    // aici sunt tipurile de inamici pe care o sa le randomizez
    // iau pe tipuri de hexagoane
    // la inceput, fiecare vector din ala e gol si tre sa pun selected in el si acel selected se tot modifica =))
    int appearanceTimeHex1 = rand() % 5000; 

    currentTime += deltaTimeSeconds; 
	if (currentTime > appearanceTimeHex1 * 30) {
		for (int i = 0; i < 3; i++) {
			star.x = rand() % 2400;
            star.y = rand() % 1700;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(star.x, star.y);
            forma.color = glm::vec3(1,0,1);
            strcpy(forma.culoare, "roz");
            forma.mesh = meshes["star"];
            forma.scale = {1.0f, 1.0f};
            forma.coord = star;
            forma.modelMatrix = modelMatrix;
            forma.on = true; 
            stars.push_back(forma);
		}
        appearanceTimeHex1 = rand() % 10500; 
    }
    for (int i = 0; i < stars.size(); i++) {
        if (stars[i].on) {
            RenderMesh2D(stars[i].mesh, shaders["VertexColor"], stars[i].modelMatrix);
        }
    }

    // deci, la hexagoane
    // mai intai creezi formele
    // apoi cand expira timpul, dai rand la o culoare 
    // si face de culoarea aia cu poz rand

    int appearanceTimeHex2 = rand() % 500; 
	if (currentTime > appearanceTimeHex2 * 50) {
        int i = rand() % 4;
        if (i == 0) {
            forma.mesh = meshes["hexagone1"];
            strcpy(forma.culoare, "portocaliu");
            forma.color = glm::vec3(1, 0.5f, 0);
        }
        if (i == 1) {
            forma.mesh = meshes["hexagone2"];
            strcpy(forma.culoare, "albastru");
            forma.color = glm::vec3(0, 0, 1);
        }
        if (i == 2) {
            forma.mesh = meshes["hexagone3"];
            strcpy(forma.culoare, "galben");
            forma.color = glm::vec3(1, 1, 0);
        }
        if (i == 3) {
            forma.mesh = meshes["hexagone4"];
            strcpy(forma.culoare, "mov");
            forma.color = glm::vec3(0.5f, 0, 1);
        }
        hexa_coords.x = rand() % 2300;
        if (hexa_coords.x < 1000) {
            hexa_coords.x += 1200;
        }
        hexa_coords.y = rand() % 6;
        hexa_coords.y = glm::ceil(hexas[i].y);
        if (hexa_coords.y == 0 || hexa_coords.y == 2 || hexa_coords.y == 4) {
            hexa_coords.y++;
        }
        hexas.push_back(hexa_coords);
        forma.coord = hexa_coords;
        forma.scale = {1.0f, 1.0f};
        forma.modelMatrix = glm::mat3(1);
        forma.modelMatrix *= transform2D::Translate(forma.coord.x, forma.coord.y);
        forma.on = true; // asta e un default, dar se schimba in functie daca e randat sau nu
        // adica acest on indica daca apare pe ecran sau nu
        hexa.push_back(forma);

        appearanceTimeHex2 = rand() % 8500; 
    }
    
    for (int i = 0; i < hexa.size(); i++) {
        if (hexa[i].on == true) {
            hexa[i].modelMatrix = glm::mat3(1);
            hexa[i].modelMatrix *= transform2D::Translate(hexas[i].x, hexas[i].y);
            hexas[i].x -= 200 * deltaTimeSeconds;
            hexa[i].coord = hexas[i];
            RenderMesh2D(hexa[i].mesh, shaders["VertexColor"], hexa[i].modelMatrix);
        }
    }

    coordonate.x = 900; 
    coordonate.y = window->GetResolution().y / 3 + 275;
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(coordonate.x, coordonate.y);
        forma.mesh = meshes["heart"];
        strcpy(forma.culoare, "rosu");
        forma.color = glm::vec3(1, 0, 0);
        forma.scale = {1.0f, 1.0f};
        forma.coord.x = coordonate.x;
        forma.coord.y = coordonate.y;
        forma.on = true;
        forma.modelMatrix = modelMatrix;
        lives.push_back(forma);
        coordonate.x = coordonate.x + 200;
    }
        for (int i = 0; i < dias.size(); i++) {
            if (dias[i].on) {
                forma = dias[i];
                RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
            }
        }

    // depasit de hexagon
    for (int i = 0; i < dias.size(); i++) {
        for (int j = 0; j < hexa.size(); j++) {
            if (dias[i].coord.x >= hexas[j].x - 0.4f * squareSide && dias[i].coord.y == hexas[j].y) {
                // squareSide la mine e latura cumva sau un fel de arie... e gen inspirat dupa lab3
                // in plus, am cam configurat meshul sa fie 0.8 sau 0.4 din latura data ca parametru la creare, care e 100 btw
                // cam aceeasi idee e si la coliziunea cealalta
                // toate formele mele au length ca lungime data ca argument, dar e calculat altfel, gen
                // in functie de forma, o latura variaza intre 0.1 si 0.8 * length si sunt egal departate de centru
                // la mine mereu centrul va fi 0.0 si sqareside-ul, adica lungimea, 100, acum cum pun eu diferitele coordonate
               if (strcmp(dias[i].culoare, hexa[j].culoare) != 0) {
                        dias[i].scale.x -= 2.0f *deltaTimeSeconds;
                        dias[i].scale.y -= 2.0f *deltaTimeSeconds;
                        dias[i].modelMatrix *= transform2D::Scale(dias[i].scale.x, dias[i].scale.y);
                        if (dias[i].scale.x < 0 && dias[i].scale.y < 0) {
                            dias[i].on = false;
                            dias[i].scale.x = 1;
                            dias[i].scale.y = 1;
                        }
                    }
                    if ((dias[i].color.r == 1) && (dias[i].color.g == 0.5f) && (dias[i].color.b == 0) &&
                    (hexa[j].color.r == 1) && (hexa[j].color.g == 1) && (hexa[j].color.b == 0) ){
                        if (strcmp(dias[i].culoare, hexa[j].culoare) != 0) {
                            dias[i].scale.x -= 2.0f *deltaTimeSeconds;
                            dias[i].scale.y -= 2.0f *deltaTimeSeconds;
                            dias[i].modelMatrix *= transform2D::Scale(dias[i].scale.x, dias[i].scale.y);
                            if (dias[i].scale.x < 0 && dias[i].scale.y < 0) {
                                dias[i].on = false;
                                dias[i].scale.x = 1;
                                dias[i].scale.y = 1;
                            }
                        }
                    }
                    if ((dias[i].color.r == 1) && (dias[i].color.g == 1) && (dias[i].color.b == 0) &&
                    (hexa[j].color.r == 1) && (hexa[j].color.g == 0.5f) && (hexa[j].color.b == 0) ){
                        if (strcmp(dias[i].culoare, hexa[j].culoare) != 0) {
                            dias[i].scale.x -= 2.0f *deltaTimeSeconds;
                            dias[i].scale.y -= 2.0f *deltaTimeSeconds;
                            dias[i].modelMatrix *= transform2D::Scale(dias[i].scale.x, dias[i].scale.y);
                            if (dias[i].scale.x < 0 && dias[i].scale.y < 0) {
                                dias[i].on = false;
                                dias[i].scale.x = 1;
                                dias[i].scale.y = 1;
                            }
                        }
                    }
                    if ((dias[i].color.r == 0) && (dias[i].color.g == 0) && (dias[i].color.b == 1) &&
                    (hexa[j].color.r == 0.5) && (hexa[j].color.g == 0) && (hexa[j].color.b == 1) ){
                        if (strcmp(dias[i].culoare, hexa[j].culoare) != 0) {
                            dias[i].scale.x -= 2.0f *deltaTimeSeconds;
                            dias[i].scale.y -= 2.0f *deltaTimeSeconds;
                            dias[i].modelMatrix *= transform2D::Scale(dias[i].scale.x, dias[i].scale.y);
                            if (dias[i].scale.x < 0 && dias[i].scale.y < 0) {
                                dias[i].on = false;
                                dias[i].scale.x = 1;
                                dias[i].scale.y = 1;
                            }
                        }
                    }
                    if ((dias[i].color.r == 0.5) && (dias[i].color.g == 0) && (dias[i].color.b == 1) &&
                    (hexa[j].color.r == 0) && (hexa[j].color.g == 0) && (hexa[j].color.b == 1) ){
                        if (strcmp(dias[i].culoare, hexa[j].culoare) != 0) {
                            dias[i].scale.x -= 2.0f *deltaTimeSeconds;
                            dias[i].scale.y -= 2.0f *deltaTimeSeconds;
                            dias[i].modelMatrix *= transform2D::Scale(dias[i].scale.x, dias[i].scale.y);
                            if (dias[i].scale.x < 0 && dias[i].scale.y < 0) {
                                dias[i].on = false;
                                dias[i].scale.x = 1;
                                dias[i].scale.y = 1;
                            }
                        }
                    }
                }
            }
        }
        if (!hexa.empty()) {
        // coliziune cu dreptunghiul rosu
        for (int j = 0; j < hexa.size(); j++) {
            if (hexa[j].coord.x <= rectangle.coord.x + 0.9f * 100 && hexa[j].on) { 
                // 1.8 * 100 e latimea
                aici = j;
                if (remainingLives != 0) {
                    hexa[aici].scale.x -= 0.002f *deltaTimeSeconds;
                    hexa[aici].scale.y -= 0.002f *deltaTimeSeconds;
                    hexa[aici].modelMatrix *= transform2D::Scale(hexa[aici].scale.x, hexa[aici].scale.y);
                    if (hexa[aici].scale.x < 0 && hexa[aici].scale.y < 0) {
                        // hexa[aici].on = false;
                        hexa.erase(hexa.begin() + aici);
                        hexas.erase(hexas.begin() + aici);
                        break;
                    }
                    remainingLives--;
                }
                else {
                    hexa[aici].scale.x -= 0.002f *deltaTimeSeconds;
                    hexa[aici].scale.y -= 0.002f *deltaTimeSeconds;
                    hexa[aici].modelMatrix *= transform2D::Scale(hexa[aici].scale.x, hexa[aici].scale.y);
                    if (hexa[aici].scale.x < 0.1f && hexa[aici].scale.y < 0.1f) {
                        // hexa[aici].on = false;
                        hexa.erase(hexa.begin() + aici);
                        hexas.erase(hexas.begin() + aici);
                        break;
                    }
                }
                hexa.erase(hexa.begin() + aici);
                hexas.erase(hexas.begin() + aici);
            }
        }
    }

    for (int i = 0; i < hexa.size(); i++) {
        forma = hexa[i];
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    }

    for (int i = 0; i < remainingLives; i++) {
        forma = lives[i];
        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    }
   
    // acum iau pe tipuri de proiectile
    for (int i = 0; i < dias.size(); i++) {
    coords old = dias[i].coord;
        for (int j = 0; j < hexa.size(); j++) {
            if (dias[i].coord.y == hexas[j].y && dias[i].color == hexa[j].color && dias[i].on 
            && strcmp(dias[i].culoare, hexa[j].culoare)== 0) {
                if (strcmp(dias[i].culoare, "portocaliu") == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                    RenderMesh2D(meshes["pr1"], shaders["VertexColor"],modelMatrix); // am randat steluta
                }
                if (strcmp(dias[i].culoare, "galben") == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                    RenderMesh2D(meshes["pr3"], shaders["VertexColor"],modelMatrix); // am randat steluta
                
                }
                if (strcmp(dias[i].culoare, "albastru") == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                    RenderMesh2D(meshes["pr2"], shaders["VertexColor"],modelMatrix); // am randat steluta
                }
                if (strcmp(dias[i].culoare, "mov") == 0) {
                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                    RenderMesh2D(meshes["pr4"], shaders["VertexColor"],modelMatrix); // am randat steluta
                }
                RenderMesh2D(prs[i].mesh, shaders["VertexColor"],prs[i].modelMatrix); // am randat steluta
                prs[i].modelMatrix = glm::mat3(1);
                prs[i].coord.x += 300 * deltaTimeSeconds;
                prs[i].modelMatrix *= transform2D::Translate(prs[i].coord.x, prs[i].coord.y);
                prs[i].modelMatrix *= transform2D::Rotate(angularStep);
                angularStep = angularStep + 5 * deltaTimeSeconds;
                if (prs[i].coord.x >= hexas[j].x - 0.4f * squareSide) {
                    if (strcmp(dias[i].culoare, "portocaliu") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr1"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                    if (strcmp(dias[i].culoare, "galben") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr3"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    
                    }
                    if (strcmp(dias[i].culoare, "albastru") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr2"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                    if (strcmp(dias[i].culoare, "mov") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr4"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                    prs[i].modelMatrix = glm::mat3(1);
                    prs[i].scale = {0, 0};
                    prs[i].modelMatrix *= transform2D::Scale(prs[i].scale.x, prs[i].scale.y);
                    prs[i].modelMatrix = glm::mat3(1);
                    prs[i].scale = {1, 1};
                    prs[i].coord.x = old.x;
                    prs[i].modelMatrix *= transform2D::Translate(old.x, prs[i].coord.y);
                    nr++;
                    if (strcmp(dias[i].culoare, "portocaliu") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr1"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                    if (strcmp(dias[i].culoare, "galben") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr3"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    
                    }
                    if (strcmp(dias[i].culoare, "albastru") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr2"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                    if (strcmp(dias[i].culoare, "mov") == 0) {
                        modelMatrix = glm::mat3(1);
                        modelMatrix *= transform2D::Translate(dias[i].coord.x + 50, dias[i].coord.y);
                        RenderMesh2D(meshes["pr4"], shaders["VertexColor"],modelMatrix); // am randat steluta
                    }
                }
                if (nr >= 3) {
                    hexa[j].scale.x -= 0.02f *deltaTimeSeconds;
                    hexa[j].scale.y -= 0.02f *deltaTimeSeconds;
                    hexa[j].modelMatrix *= transform2D::Scale(hexa[j].scale.x, hexa[j].scale.y);
                    if (hexa[j].scale.x < 0.1f && hexa[j].scale.y < 0.1f) {
                        aci = j;
                        hexa[j].on = false;
                        hexa.erase(hexa.begin() + aici);
                        hexas.erase(hexas.begin() + aici);
                        nr = 0;
                        break;
                    }
                    hexa.erase(hexa.begin() + aci);
                    hexas.erase(hexas.begin() + aci);
                    nr = 0;
                } 
            }
        }
    }
    for (int i = 0; i < stars.size(); i++) {
        RenderMesh2D(stars[i].mesh, shaders["VertexColor"], stars[i].modelMatrix);
    }
    if (stele < 0) {
        stele = 0;
    }
}

void Lab3::FrameEnd() {
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
   
}

void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    if (hold) {
        // hold = false;
   // }
        // forma.on = false;
        // forma.modelMatrix = glm::mat3(1);
        // RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);

       
      //  forma.on = true;
      forma.coord.x = 2 * mouseX;
        forma.coord.y = (720 - mouseY) * 2;
        forma.modelMatrix = glm::mat3(1);
        forma.modelMatrix *= transform2D::Translate(forma.coord.x, forma.coord.y);

        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);
    }
}

void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        hold = true;
        for (int j = 0; j < 9; j = j + 2) {
        // sunt 4 cadrane, 4 tipuri de romburi, dar in aia de mapare am colt st jos urmat de colt dr sus ca sa pot lua range-ul
        // gen map[i] e colt st jos si map[i+1] e coltul dr sus al aceleiasi forme
        // deci da, asta se stie cate tipuri de dealea sunt
            if (mouseX >= cadrane_map[j].x &&
                mouseX <= cadrane_map[j + 1].x &&
                mouseY <= cadrane_map[j].y &&
                mouseY >= cadrane_map[j + 1].y) {
                selected = j / 2;
                odata = true;
            }
        }

       
        if (selected == 0) {
            forma.mesh = meshes["diamond1"];
            forma.color = glm::vec3(1, 0.5f, 0);
            strcpy(forma.culoare, "portocaliu");
        }
        if (selected == 1) {
            forma.mesh = meshes["diamond2"];
            forma.color = glm::vec3(0, 0, 1);
            strcpy(forma.culoare, "albastru");
        }
        if (selected == 2) {
            forma.mesh = meshes["diamond3"];
            forma.color = glm::vec3(1, 1, 0);
            strcpy(forma.culoare, "galben");
        }
        if (selected == 3) {
            forma.mesh = meshes["diamond4"];
            forma.color = glm::vec3(0.5f, 0, 1);
            strcpy(forma.culoare, "mov");
        }
        forma.coord.x = 2 * mouseX;
        forma.on = true;
        forma.coord.y = (720 - mouseY) * 2;
        forma.modelMatrix = glm::mat3(1);
        forma.modelMatrix *= transform2D::Translate(forma.coord.x, forma.coord.y);

        RenderMesh2D(forma.mesh, shaders["VertexColor"], forma.modelMatrix);


        if (selected == 0 && odata) {
            stele--;
            odata = false;
        }
        if ((selected == 1 || selected == 2) && odata) {
            stele -= 2;
            odata = false;
        }
        if (selected == 3 && odata) {
            stele -= 3;
            odata = false;
        }
        for (int i = 0; i < stars.size(); i++) {
            if (mouseX * 2 >= stars[i].coord.x - 0.4f * 100 && mouseX * 2 <= stars[i].coord.x + 0.4f * 100
            && (720 - mouseY) * 2 >= stars[i].coord.y - 0.4f * 100 && (720 - mouseY) * 2 <= stars[i].coord.y + 0.4f * 100) {
                stars[i].on = false;
                stele++;
                stars[i].coord.x = 2900;
                stars[i].coord.y = 2900;
                stars[i].modelMatrix *= transform2D::Translate(stars[i].coord.x, stars[i].coord.y);
            }
            if (stars[i].on) {
                RenderMesh2D(stars[i].mesh, shaders["VertexColor"], stars[i].modelMatrix);
            }
        }
    }
}

void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (button == 1 && hold) {
        hold = false;
    }
    if (button == 1) {
        if (mouseX >= 100 && mouseX <= 175 &&
            mouseY <= 704 && mouseY >= 629) {
            // patrat 1
            temporaryRombPosition.x = squares[0].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 100;
        }
        if (mouseX >= 200 && mouseX <= 275 &&
            mouseY <= 704 && mouseY >= 629) {
            // patrat 2
            temporaryRombPosition.x = squares[1].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 100;
        }
        if (mouseX >= 300 && mouseX <= 375 &&
            mouseY <= 704 && mouseY >= 629) {
            // patrat 3
            temporaryRombPosition.x = squares[2].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 100;
        }
        if (mouseX >= 100 && mouseX <= 175 &&
            mouseY <= 604 && mouseY >= 529) {
            // patrat 4
            temporaryRombPosition.x = squares[3].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 300;
        }
        if (mouseX >= 200 && mouseX <= 275 &&
            mouseY <= 604 && mouseY >= 529) {
            // patrat 5
            temporaryRombPosition.x = squares[4].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 300;
        }
        if (mouseX >= 300 && mouseX <= 375 &&
            mouseY <= 604 && mouseY >= 529) {
            // patrat 6
            temporaryRombPosition.x = squares[5].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 300;
        }
        if (mouseX >= 100 && mouseX <= 175 &&
            mouseY <= 504 && mouseY >= 429) {
            // patrat 7
            temporaryRombPosition.x = squares[6].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 500;
        }
        if (mouseX >= 200 && mouseX <= 275 &&
            mouseY <= 504 && mouseY >= 429) {
            // patrat 8
            temporaryRombPosition.x = squares[7].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 500;
        }
        if (mouseX >= 300 && mouseX <= 375 &&
            mouseY <= 504 && mouseY >= 429) {
            // patrat 9
            temporaryRombPosition.x = squares[8].coord.x + 100 * 3 / 4;
            temporaryRombPosition.y = 500;
        }
        if (selected == 0) {
            forma.mesh = meshes["diamond1"];
            forma.color = glm::vec3(1, 0.5f, 0);
            strcpy(forma.culoare, "portocaliu");

            forma2.mesh = meshes["pr1"];
            forma2.color = glm::vec3(1, 0.5f, 0);
            strcpy(forma2.culoare, "portocaliu");
        }
        if (selected == 1) {
            forma.mesh = meshes["diamond2"];
            forma.color = glm::vec3(0, 0, 1);
            strcpy(forma.culoare, "albastru");

            forma2.mesh = meshes["pr2"];
            forma2.color = glm::vec3(0, 0, 1);
            strcpy(forma2.culoare, "albastru");
        }
        if (selected == 2) {
            forma.mesh = meshes["diamond3"];
            forma.color = glm::vec3(1, 1, 0);
            strcpy(forma.culoare, "galben");

            forma2.mesh = meshes["pr3"];
            forma2.color = glm::vec3(1, 1, 0);
            strcpy(forma2.culoare, "galben");
        }
        if (selected == 3) {
            forma.mesh = meshes["diamond4"];
            forma.color = glm::vec3(0.5f, 0, 1);
            strcpy(forma.culoare, "mov");

            forma2.mesh = meshes["pr4"];
            forma2.color = glm::vec3(0.5f, 0, 1);
            strcpy(forma2.culoare, "mov");
        }
        forma.modelMatrix = glm::mat3(1);
        forma.scale = {1.0f, 1.0f};
        forma.coord = temporaryRombPosition;
        forma.on = true;
        forma.modelMatrix *= transform2D::Translate(forma.coord.x, forma.coord.y);
        dias.push_back(forma);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(temporaryRombPosition.x + 100 * 3 / 4 + 150, temporaryRombPosition.y);
        forma2.scale = {1.0f, 1.0f};
        forma2.coord.x = temporaryRombPosition.x + 100 * 3 / 4 + 150;
        forma2.coord.y = temporaryRombPosition.y;
        forma2.on = false;
        forma2.modelMatrix = modelMatrix;
        prs.push_back(forma2);
    }
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
