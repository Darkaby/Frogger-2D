/*
 * Widget Game: Configuration du jeu Frogger
 * Fichier: game.h
 * Auteurs:
 * * Gabrielle TCHUENBOU KOMGUEP
 * * Ayinde OLUTCHI
 * * Ahmet DUMLU
 */

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <math.h>
#include "truck.h"

// Nombre de véhicules dans chaque ligne
#define N1 3
#define N2 5
#define N3 4
#define N4 6
#define N5 4

// Chemin complet vers l'image
const char PATH[] = "D:/Documents/ESIEA/Cours 5e année/Majeure Systèmes Embarqués/Conception IHM/Qt Projects/";

class Game : public QWidget
{
    Q_OBJECT

public:
    Game(int step, int time);

    void displayInfoBox(QString title, QString message, bool start);
    void showInfoBox();
    void initTrucks(int step); // Initialiser les positions et pas des véhicules
    void animate(QPainter* painter, Truck truck[], int num); // Animer tous les bus
    void validExit(QPainter* painter);

    bool testCollisionsBus(Truck* a, QLabel* b); // Tester la collision entre le frog et un bus
    int getScore();

protected:
    void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *keyEvent) Q_DECL_OVERRIDE;


public slots:
    void setScore(int score);
    void setLabelScore();

private:
    // Lignes de bus
    Truck m_trucks_line1[N1];
    Truck m_trucks_line2[N2];
    Truck m_trucks_line3[N3];
    Truck m_trucks_line4[N4];
    Truck m_trucks_line5[N5];

    // Dessin des sorties du jeu
    QPointF m_points_S1[8] = {
        QPointF(0.0, 50.0),
        QPointF(250.0, 50.0),
        QPointF(250.0, 230.0),
        QPointF(160.0, 230.0),
        QPointF(160.0, 160.0),
        QPointF(90.0, 160.0),
        QPointF(90.0, 230.0),
        QPointF(0.0, 230.0),
    };
    QPointF m_points_S2[8] = {
        QPointF(250.0, 50.0),
        QPointF(500.0, 50.0),
        QPointF(500.0, 230.0),
        QPointF(410.0, 230.0),
        QPointF(410.0, 160.0),
        QPointF(340.0, 160.0),
        QPointF(340.0, 230.0),
        QPointF(250.0, 230.0),
    };
    QPointF m_points_S3[8] = {
        QPointF(500.0, 50.0),
        QPointF(750.0, 50.0),
        QPointF(750.0, 230.0),
        QPointF(660.0, 230.0),
        QPointF(660.0, 160.0),
        QPointF(590.0, 160.0),
        QPointF(590.0, 230.0),
        QPointF(500.0, 230.0),
    };
    QPointF m_points_S4[8] = {
        QPointF(750.0, 50.0),
        QPointF(1000.0, 50.0),
        QPointF(1000.0, 230.0),
        QPointF(910.0, 230.0),
        QPointF(910.0, 160.0),
        QPointF(840.0, 160.0),
        QPointF(840.0, 230.0),
        QPointF(750.0, 230.0),
    };

    // Coordonées en X des sorties du jeu
    int m_exitX[4] = {100, 350, 600, 850};
    // Etat des sorties
    bool m_exit[4] = {false, false, false, false};

    int m_score = 0; // Score
    int m_hits = 0; // Nombre de collisions

    QWidget* m_msgBox; // Boîte de dialogue
    QLabel* m_frog; // Joueur
    QLabel* m_label_score; // Label : Score + Hits
    QTimer* m_timer; // Timer
    QPixmap* m_pixmap; // Image joueur
};

#endif // GAME_H
