/*
 * Widget Game: Configuration du jeu Frogger
 * Fichier: game.cpp
 * Auteurs:
 * * Gabrielle TCHUENBOU KOMGUEP
 * * Ayinde OLUTCHI
 * * Ahmet DUMLU
 */

#include "game.h"
#include <QVBoxLayout>
#include <QPushButton>


Game::Game(int step, int time) : QWidget()
{
    setFixedSize(1000, 800);
    setStyleSheet("background-color: black");

    //Info box
    displayInfoBox("Bienvenue", "Commandes du jeu: Utiliser les flèches du clavier pour déplacer"
                                " le chat.", true);

    // Label Score
    m_label_score = new QLabel("Score :", this);
    m_label_score->setGeometry(0, 0, 1000, 50);
    m_label_score->setStyleSheet("background-color: gray");
    m_label_score->setFont(QFont("Cambria", 22));

    // Player: Frog
    m_frog = new QLabel("MOVE", this);
    m_pixmap = new QPixmap(PATH + QString("cat.png"));
    m_frog->setGeometry(800, 730, 50, 50);
    *m_pixmap = m_pixmap->scaled(m_frog->size(), Qt::IgnoreAspectRatio, Qt::FastTransformation); // Ajuster la taille du pixmap à celle du label
    m_frog->setPixmap(*m_pixmap);

    // Initialisation des bus
    initTrucks(step);

    // Affichage des commandes du jeu
    m_msgBox->show();

    // Timer
    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, this, QOverload<>::of(&Game::update));
    m_timer->start(time);
}

// Afficher la boîte de dialogue
void Game::displayInfoBox(QString title, QString message, bool start)
{
    QVBoxLayout* layout = new QVBoxLayout;
    QPushButton* exit = new QPushButton("Fermer");
    QLabel* info = new QLabel(message);

    // Propriétés de la fenêtre et ajout des widgets
    m_msgBox = new QWidget();
    m_msgBox->setWindowTitle(title);
    m_msgBox->setGeometry(50, 100, 500, 100);

    //m_infoBox = new QLabel(message);
    info->setFont(QFont("Cambria", 10));
    layout->addWidget(info);
    layout->addWidget(exit);
    m_msgBox->setLayout(layout);

    // Fermer toutes les fenêtres à la fin du jeu
    QWidget::connect(exit, &QPushButton::clicked, m_msgBox, &QWidget::close);
    if (start == false)
        QWidget::connect(exit, &QPushButton::clicked, this, &Game::close);
}

// Initialisation des bus
void Game::initTrucks(int step)
{
    int i, pos = 0; // position of the first truck (x)

    // Trucks on line 1
    for (i=0; i<N1; i++)
    {
        m_trucks_line1[i].setParent(this);
        m_trucks_line1[i].init(pos, 630, 150, step);
        pos+=380;
    }

    // Trucks on line 2
    pos = 830;
    for (i=0; i<N2; i++)
    {
        m_trucks_line2[i].setParent(this);
        m_trucks_line2[i].init(pos, 530, 115, -step);
        pos-=223;
    }

    // Trucks on line 3
    pos = 250;
    for (i=0; i<N3; i++)
    {
        m_trucks_line3[i].setParent(this);
        m_trucks_line3[i].init(pos, 430, 120, step+10);
        pos+=280;
    }

    // Trucks on line 4
    pos = 900;
    for (i=0; i<N4; i++)
    {
        m_trucks_line4[i].setParent(this);
        m_trucks_line4[i].init(pos, 330, 50, step-25);
        pos-=175;
    }

    // Trucks on line 5
    pos = 140;
    for (i=0; i<N5; i++)
    {
        m_trucks_line5[i].setParent(this);
        m_trucks_line5[i].init(pos, 230, 140, step+5);
        pos+=285;
    }

}

// Test des collisions entre frog et truck
bool Game::testCollisionsBus(Truck* a, QLabel* b)
{
    int dx = b->x() - a->X();
    int dy = b->y() - a->Y();

    if (dx < a->Width() && dx > -b->width())
        if (std::fabs(dy) < b->height())
            return true;
    else
        return false;
}

// Animer les bus et revenir au point de départ lors de collisions
void Game::animate(QPainter* painter, Truck truck[], int num)
{
    for (int i=0; i<num; i++)
    {
        painter->drawRect(truck[i].X(), truck[i].Y(), truck[i].width(), truck[i].height());
        truck[i].animate();

        if (testCollisionsBus(&truck[i], m_frog)){
            m_frog->setGeometry(800, 730, 50, 50);
            m_hits++;
        }
    }
}

void Game::validExit(QPainter* painter)
{
    for (int i=0; i<4; i++)
    {
        if (m_exit[i] == false && (m_frog->x() == m_exitX[i] && m_frog->y() == 180))
        {
            m_exit[i] = true; // Sortie validée
            m_score++; // Mise à jour du score
        }
        else if (m_exit[i] == true)
            painter->drawRect(m_exitX[i], 180, 50, 50); // Marquer la sortie comme bloquée

        if (m_frog->x() == m_exitX[i] && m_frog->y() == 180)
            // Création d'un nouveau frog
            m_frog->setGeometry(800, 730, 50, 50);
    }
}

int Game::getScore()
{
    return m_score;
}

void Game::setScore(int score)
{
    m_score = score;
}

void Game::setLabelScore()
{
    m_label_score->setText("\tScore : " + QString::number(m_score) + " \t\t\t Hits: " + QString::number(m_hits));
}

void Game::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // Draw the exits
    painter.setBrush(QBrush(Qt::green, Qt::Dense1Pattern));
    painter.drawPolygon(m_points_S1, 8);
    painter.drawPolygon(m_points_S2, 8);
    painter.drawPolygon(m_points_S3, 8);
    painter.drawPolygon(m_points_S4, 8);

    // Animate Trucks
    painter.setBrush(QBrush(Qt::magenta, Qt::Dense3Pattern));
    animate(&painter, m_trucks_line1, N1);
    painter.setBrush(QBrush(Qt::red, Qt::Dense3Pattern));
    animate(&painter, m_trucks_line2, N2);
    painter.setBrush(QBrush(Qt::white, Qt::Dense3Pattern));
    animate(&painter, m_trucks_line3, N3);
    painter.setBrush(QBrush(Qt::blue, Qt::Dense3Pattern));
    animate(&painter, m_trucks_line4, N4);
    painter.setBrush(QBrush(Qt::yellow, Qt::Dense3Pattern));
    animate(&painter, m_trucks_line5, N5);

    // Test de collisions au niveau des sorties
    if ((m_frog->x() >= 0 && m_frog->x() <= 90) || (m_frog->x() >= 160 && m_frog->x() <= 340)
              || (m_frog->x() >= 410 && m_frog->x() <= 590)|| (m_frog->x() >= 660 && m_frog->x() <= 840)
              || (m_frog->x() >= 910 && m_frog->x() <= 1000))
        if (m_frog->y() < 230) {
            m_frog->setGeometry(800, 730, 50, 50);
            m_hits++;
        }

    // Set score
    painter.setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
    validExit(&painter);
    setLabelScore();

    // Jeu terminé
    if (m_score == 4)
    {
        QString msg = "Bravo! Vous venez de terminer le jeu avec " + QString::number(m_hits) + " hits!";
        displayInfoBox("Félicitations!", msg, false);
        m_msgBox->show();
        m_score = 0; m_hits = 0; // Réinitialistaion
    }
}

void Game::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key()) {

    case Qt::Key_Up:
        m_frog->move(m_frog->x(), m_frog->y()-50);
        break;

    case Qt::Key_Down:
        m_frog->move(m_frog->x(), m_frog->y()+50);
        break;

    case Qt::Key_Right:
        m_frog->move(m_frog->x()+25, m_frog->y());
        break;

    case Qt::Key_Left:
        m_frog->move(m_frog->x()-25, m_frog->y());
        break;

    default:
        break;

    }
}
