#include "applicgaragewindow.h"
#include "ui_applicgaragewindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <sstream>
#include <qdebug.h>

using namespace std;

#define REPERTOIRE_IMAGES "images/"

ApplicGarageWindow::ApplicGarageWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::ApplicGarageWindow)
{
    ui->setupUi(this);

    // Configuration de la table des options (projet en cours)
    ui->tableWidgetOptions->setColumnCount(3);
    ui->tableWidgetOptions->setRowCount(5);
    for (int i = 0; i < 5; i++)
        ui->tableWidgetOptions->setRowHeight(i, 10);
    QStringList labelsTableOptions;
    labelsTableOptions << "Code"
                       << "Prix"
                       << "Intitulé";
    ui->tableWidgetOptions->setHorizontalHeaderLabels(labelsTableOptions);
    ui->tableWidgetOptions->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetOptions->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetOptions->horizontalHeader()->setVisible(true);
    ui->tableWidgetOptions->horizontalHeader()->setDefaultSectionSize(60);
    ui->tableWidgetOptions->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetOptions->verticalHeader()->setVisible(false);
    ui->tableWidgetOptions->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des employes (Personnel Garage)
    ui->tableWidgetEmployes->setColumnCount(4);
    ui->tableWidgetEmployes->setRowCount(0);
    QStringList labelsTableEmployes;
    labelsTableEmployes << "Numéro"
                        << "Nom"
                        << "Prénom"
                        << "Fonction";
    ui->tableWidgetEmployes->setHorizontalHeaderLabels(labelsTableEmployes);
    ui->tableWidgetEmployes->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetEmployes->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetEmployes->horizontalHeader()->setVisible(true);
    ui->tableWidgetEmployes->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetEmployes->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetEmployes->verticalHeader()->setVisible(false);
    ui->tableWidgetEmployes->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des clients
    ui->tableWidgetClients->setColumnCount(4);
    ui->tableWidgetClients->setRowCount(0);
    QStringList labelsTableClients;
    labelsTableClients << "Numéro"
                       << "Nom"
                       << "Prénom"
                       << "GSM";
    ui->tableWidgetClients->setHorizontalHeaderLabels(labelsTableClients);
    ui->tableWidgetClients->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetClients->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetClients->horizontalHeader()->setVisible(true);
    ui->tableWidgetClients->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetClients->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetClients->verticalHeader()->setVisible(false);
    ui->tableWidgetClients->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Configuration de la table des contrats
    ui->tableWidgetContrats->setColumnCount(4);
    ui->tableWidgetContrats->setRowCount(0);
    QStringList labelsTableContrats;
    labelsTableContrats << "Numéro"
                        << "Vendeur"
                        << "Client"
                        << "Voiture";
    ui->tableWidgetContrats->setHorizontalHeaderLabels(labelsTableContrats);
    ui->tableWidgetContrats->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidgetContrats->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidgetContrats->horizontalHeader()->setVisible(true);
    ui->tableWidgetContrats->horizontalHeader()->setDefaultSectionSize(80);
    ui->tableWidgetContrats->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidgetContrats->verticalHeader()->setVisible(false);
    ui->tableWidgetContrats->horizontalHeader()->setStyleSheet("background-color: lightyellow");

    // Importation des modeles (étape 10)
    // TO DO

    Garage ::getInstance().importeModeles("Modeles.csv");
    Modele m;
    int i = 0;

    Vecteur<Modele> tmpm = Garage::getInstance().getModeles(); // Fix wtf
    Iterateur<Modele> itm(tmpm);
    itm.reset();

    while (!itm.end())
    {

        m = Garage::getInstance().getModele(i); // Garage::getInstance().getModele(i);
        ajouteModeleDisponible(m.getNom(), m.getPrixDeBase());
        i++;
        itm++;
    }
    // Importation des options (étape 10)
    // TO DO
    Garage ::getInstance().importeOptions("Options.csv");
    Vecteur<Option> tmpo = Garage::getInstance().getOptions();

    Iterateur<Option> ito(tmpo);

    ito.reset();
    Option o;
    i = 0;
    while (!ito.end())
    {
        o = Garage::getInstance().getOption(i);
        ajouteOptionDisponible(o.getIntitule(), o.getPrix());
        i++;
        ito++;
    }

    // Ouverture (et/ou creation) du fichier Garage.data (étape 12)
    // TO DO

    ifstream fichier("Garage.data", ios::in);

    if (!fichier)
    {
        ofstream fichier_out("Garage.data", ios::out);
        if (!fichier_out)
        {
            dialogueMessage("Chargement", "Impossible de sauvegarder le projet en cours !");

        }
        else{
            
            Garage:: getInstance().ajouteEmploye("Emma", "Karen Ah", "Emma", "Administratif");
            Garage::getInstance().Save(fichier_out);
            fichier_out.close();
        }
    }
    else
    {
        Garage::getInstance().Load(fichier);
        fichier.close();
        dialogueMessage("Chargement", "Chargement réussi !");
    }
    
    Vecteur<Employe> tmp = Garage::getInstance().getEmployes();
    Iterateur<Employe> ite(tmp);
    ite.reset();
    
    i = 0;

    while (!ite.end())
    {
        ajouteTupleTableEmployes(tmp[i].Tuple());
        i++;
        ite++;
    }

    Vecteur<Client> tmpc = Garage::getInstance().getClients();
    Iterateur<Client> itc(tmpc);
    itc.reset();
    
    i = 0;

    while (!itc.end())
    {
        ajouteTupleTableClients(tmpc[i].Tuple());
        i++;
        itc++;
    }

    Vecteur<Contrat> tmpcontrat = Garage::getInstance().getContrat();
    Iterateur<Contrat> itcontrat(tmpcontrat);
    itcontrat.reset();
    
    i = 0;

    while (!itcontrat.end())
    {
        ajouteTupleTableContrats(tmpcontrat[i].Tupple());
        i++;
        itcontrat++;
    }
    
    //setRole(); // acces a tout pour l'instant

}

ApplicGarageWindow::~ApplicGarageWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Titre de la fenêtre (ne pas modifier) //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTitre(string titre)
{
    this->setWindowTitle(titre.c_str());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion des roles (ne pas modifier) ////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setRole(int val)
{
    // val = 0 --> personne n'est loggé
    // val = 1 --> un administratif est loggé
    // val = 2 --> un vendeur loggé
    // val = 3 --> on a accès à tout

    if (val == 0)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(false);
        ui->actionReset_Mot_de_passe->setEnabled(false);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(false);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(false);
    }

    if (val == 1)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(false);
        ui->menuVoiture->setEnabled(false);
        ui->comboBoxModelesDisponibles->setEnabled(false);
        ui->comboBoxOptionsDisponibles->setEnabled(false);
        ui->pushButtonOuvrirProjet->setEnabled(false);
        ui->pushButtonNouveauProjet->setEnabled(false);
        ui->pushButtonReduction->setEnabled(false);
        ui->pushButtonEnregistrerProjet->setEnabled(false);
        ui->pushButtonAjouterOption->setEnabled(false);
        ui->pushButtonSupprimerOption->setEnabled(false);
        ui->pushButtonChoisirModele->setEnabled(false);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(false);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 2)
    {
        ui->actionLogin->setEnabled(false);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(false);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }

    if (val == 3)
    {
        ui->actionLogin->setEnabled(true);
        ui->actionLogout->setEnabled(true);
        ui->actionReset_Mot_de_passe->setEnabled(true);
        ui->menuEmployes->setEnabled(true);
        ui->menuClients->setEnabled(true);
        ui->menuVoiture->setEnabled(true);
        ui->comboBoxModelesDisponibles->setEnabled(true);
        ui->comboBoxOptionsDisponibles->setEnabled(true);
        ui->pushButtonOuvrirProjet->setEnabled(true);
        ui->pushButtonNouveauProjet->setEnabled(true);
        ui->pushButtonReduction->setEnabled(true);
        ui->pushButtonEnregistrerProjet->setEnabled(true);
        ui->pushButtonAjouterOption->setEnabled(true);
        ui->pushButtonSupprimerOption->setEnabled(true);
        ui->pushButtonChoisirModele->setEnabled(true);
        ui->pushButtonVisualiserVoiture->setEnabled(true);
        ui->pushButtonNouveauContrat->setEnabled(true);
        ui->pushButtonSupprimerContrat->setEnabled(true);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Table des options du projet en cours (ne pas modifier) /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setTableOption(int indice, string code, string intitule, float prix)
{
    // Modifie l'option de la ligne correspondant à l'indice fourni dans la table des options de l'interface graphique
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(code.c_str());
    ui->tableWidgetOptions->setItem(indice, 0, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    char tmp[20];
    sprintf(tmp, "%.2f", prix);
    if (prix < 0.0)
        item->setText("");
    else
        item->setText(tmp);
    ui->tableWidgetOptions->setItem(indice, 1, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(intitule.c_str());
    ui->tableWidgetOptions->setItem(indice, 2, item);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableOption()
{
    for (int i = 0; i < 5; i++)
        setTableOption(i);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeTable() const
{
    // retourne l'indice de l'option selectionnee dans la table des options
    QModelIndexList liste = ui->tableWidgetOptions->selectionModel()->selectedRows();
    if (liste.size() == 0)
        return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combobox des modèles disponibles (ne pas modifier) /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteModeleDisponible(const char *nom, float prixDeBase)
{
    // ajoute un modèle dans le combobox correspondant (juste le nom et le prix)
    stringstream ss;
    char temp[20];
    sprintf(temp, "%.2f", prixDeBase);
    ss << nom << " (" << temp << ")";
    ui->comboBoxModelesDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxModelesDisponibles()
{
    ui->comboBoxModelesDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceModeleSelectionneCombobox() const
{
    // retourne l'indice du modèle selectionné dans le combobox des modèles
    return ui->comboBoxModelesDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Combox des options disponibles (ne pas modifier) ///////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteOptionDisponible(string intitule, float prix)
{
    // ajoute une option dans le combobox correspondant
    stringstream ss;
    char temp[20];
    sprintf(temp, "%.2f", prix);
    ss << intitule << " (" << temp << ")";
    ui->comboBoxOptionsDisponibles->addItem(ss.str().c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videComboboxOptionsDisponibles()
{
    ui->comboBoxOptionsDisponibles->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceOptionSelectionneeCombobox() const
{
    // retourne l'indice de l'option selectionnée dans le combobox des options
    return ui->comboBoxOptionsDisponibles->currentIndex();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Gestion du Projet en cours (ne pas modifier) ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setNomProjetEnCours(string nom)
{
    // Remplit le champ nom de l'interface graphique avec le nom reçu
    ui->lineEditNomProjet->setText(nom.c_str());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::getNomProjetEnCours() const
{
    return ui->lineEditNomProjet->text().toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setModele(string nom, int puissance, int moteur, float prixDeBase, string imageModele)
{
    // Remplit les champs correspondants dans l'interface graphique
    // pour le moteur (int) : 0=Essence, 1=Diesel, 2=Electrique, 3=Hybride
    ui->lineEditNomModele->setText(nom.c_str());
    ui->lineEditPuissance->setText(to_string(puissance).c_str());
    char tmp[20];
    sprintf(tmp, "%.2f", prixDeBase);
    ui->lineEditPrixDeBase->setText(tmp);

    ui->radioButtonEssence->setChecked(false);
    ui->radioButtonDiesel->setChecked(false);
    ui->radioButtonElectrique->setChecked(false);
    ui->radioButtonHybride->setChecked(false);

    if (moteur == 0)
        ui->radioButtonEssence->setChecked(true);
    if (moteur == 1)
        ui->radioButtonDiesel->setChecked(true);
    if (moteur == 2)
        ui->radioButtonElectrique->setChecked(true);
    if (moteur == 3)
        ui->radioButtonHybride->setChecked(true);

    // Met à jour l'image du modèle
    string cheminComplet = REPERTOIRE_IMAGES + imageModele;
    QLabel *label = new QLabel();
    label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    label->setScaledContents(true);
    QPixmap *pixmap_img = new QPixmap(cheminComplet.c_str());
    label->setPixmap(*pixmap_img);
    label->resize(label->pixmap()->size());
    ui->scrollArea->setWidget(label);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::setPrix(float prix)
{
    char tmp[20];
    sprintf(tmp, "%.2f", prix);
    ui->lineEditPrix->setText(tmp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Employes (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableEmployes(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple, tuple.c_str(), 199);
    char *tmp;

    if ((tmp = strtok(Tuple, ";")) == NULL)
        return;
    char numero[20];
    strcpy(numero, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char nom[40];
    strcpy(nom, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char prenom[40];
    strcpy(prenom, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char fonction[40];
    strcpy(fonction, tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetEmployes->rowCount();
    nbLignes++;
    ui->tableWidgetEmployes->setRowCount(nbLignes);
    ui->tableWidgetEmployes->setRowHeight(nbLignes - 1, 10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetEmployes->setItem(nbLignes - 1, 0, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetEmployes->setItem(nbLignes - 1, 1, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetEmployes->setItem(nbLignes - 1, 2, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(fonction);
    ui->tableWidgetEmployes->setItem(nbLignes - 1, 3, item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableEmployes()
{
    ui->tableWidgetEmployes->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceEmployeSelectionne()
{
    QModelIndexList liste = ui->tableWidgetEmployes->selectionModel()->selectedRows();
    if (liste.size() == 0)
        return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Clients (ne pas modifier) ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableClients(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple, tuple.c_str(), 199);
    char *tmp;

    if ((tmp = strtok(Tuple, ";")) == NULL)
        return;
    char numero[20];
    strcpy(numero, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char nom[40];
    strcpy(nom, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char prenom[40];
    strcpy(prenom, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char gsm[40];
    strcpy(gsm, tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetClients->rowCount();
    nbLignes++;
    ui->tableWidgetClients->setRowCount(nbLignes);
    ui->tableWidgetClients->setRowHeight(nbLignes - 1, 10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetClients->setItem(nbLignes - 1, 0, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(nom);
    ui->tableWidgetClients->setItem(nbLignes - 1, 1, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(prenom);
    ui->tableWidgetClients->setItem(nbLignes - 1, 2, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(gsm);
    ui->tableWidgetClients->setItem(nbLignes - 1, 3, item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableClients()
{
    ui->tableWidgetClients->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceClientSelectionne()
{
    QModelIndexList liste = ui->tableWidgetClients->selectionModel()->selectedRows();
    if (liste.size() == 0)
        return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles Table des Contrats (ne pas modifier) //////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::ajouteTupleTableContrats(string tuple)
{
    // Controle du tuple recu et parsing
    char Tuple[200];
    strncpy(Tuple, tuple.c_str(), 199);
    char *tmp;

    if ((tmp = strtok(Tuple, ";")) == NULL)
        return;
    char numero[20];
    strcpy(numero, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char vendeur[40];
    strcpy(vendeur, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char client[40];
    strcpy(client, tmp);

    if ((tmp = strtok(NULL, ";")) == NULL)
        return;
    char voiture[40];
    strcpy(voiture, tmp);

    // Ajout possible
    int nbLignes = ui->tableWidgetContrats->rowCount();
    nbLignes++;
    ui->tableWidgetContrats->setRowCount(nbLignes);
    ui->tableWidgetContrats->setRowHeight(nbLignes - 1, 10);

    QTableWidgetItem *item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignCenter);
    item->setText(numero);
    ui->tableWidgetContrats->setItem(nbLignes - 1, 0, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(vendeur);
    ui->tableWidgetContrats->setItem(nbLignes - 1, 1, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(client);
    ui->tableWidgetContrats->setItem(nbLignes - 1, 2, item);

    item = new QTableWidgetItem;
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setText(voiture);
    ui->tableWidgetContrats->setItem(nbLignes - 1, 3, item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::videTableContrats()
{
    ui->tableWidgetContrats->setRowCount(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::getIndiceContratSelectionne()
{
    QModelIndexList liste = ui->tableWidgetContrats->selectionModel()->selectedRows();
    if (liste.size() == 0)
        return -1;
    QModelIndex index = liste.at(0);
    int indice = index.row();
    return indice;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions permettant d'afficher des boites de dialogue /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueMessage(const char *titre, const char *message)
{
    QMessageBox::information(this, titre, message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::dialogueErreur(const char *titre, const char *message)
{
    QMessageBox::critical(this, titre, message);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ApplicGarageWindow::dialogueDemandeTexte(const char *titre, const char *question)
{
    QString chaine = QInputDialog::getText(this, titre, question);
    return chaine.toStdString();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ApplicGarageWindow::dialogueDemandeInt(const char *titre, const char *question)
{
    return QInputDialog::getInt(this, titre, question);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float ApplicGarageWindow::dialogueDemandeFloat(const char *titre, const char *question)
{
    return QInputDialog::getDouble(this, titre, question);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les items de menu //////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionQuitter_triggered()
{
    // TO DO (étape 12)
    ofstream fichier_out("Garage.data", ios::out);
    if (!fichier_out)
    {
        dialogueErreur("Sauvegarde", "Impossible de sauvegarder le projet !");

    }
    else
    {
        Garage ::getInstance().Save(fichier_out);
        fichier_out.close();
    }

    QApplication::exit();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::closeEvent(QCloseEvent *event)
{
    if (event == NULL)
    {
    } // pour éviter le warning
      // TO DO (étape 12)
    ofstream fichier_out("Garage.data", ios::out);
    if (!fichier_out)
    {
        dialogueErreur("Sauvegarde", "Impossible de sauvegarder le projet !");

    }
    else
    {
        Garage ::getInstance().Save(fichier_out);
        fichier_out.close();
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouveau_modele_triggered()
{
    // Saisie des informations (aucune vérification n'est faite --> à gérer si vous voulez)
    
    string nomModele = dialogueDemandeTexte("Nouveau modèle", "Nom :");
    int puissance = dialogueDemandeInt("Nouveau modèle", "Puissance :");
    int moteur = dialogueDemandeInt("Nouveau modèle :", "Moteur (0=essence,1=diesel,2=électrique,3=hybride) :");
    float prixDeBase = dialogueDemandeFloat("Nouveau modèle", "Prix de base :");
    string image = dialogueDemandeTexte("Nouveau modèle", "Nom du fichier de l'image :");

    char *buff;
    int size;
    size = nomModele.size() + 1;
    buff = new char[size];
    strcpy(buff, nomModele.c_str());

    Moteur mot = Essence;
    switch (moteur)
    {
    case 0:
        mot = Essence;
        break;

    case 1:
        mot = Diesel;
        break;

    case 2:
        mot = Electrique;
        break;

    case 3:
        mot = Hybride;
        break;
    }
    Garage::getInstance().ajouteModele(Modele(buff, puissance, mot, prixDeBase, image));

    ajouteModeleDisponible(buff, prixDeBase);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionNouvelle_option_triggered()
{
    // Saisie des informations (aucune vérification n'est faite --> à gérer si vous voulez)
    
    string code = dialogueDemandeTexte("Nouvelle option", "Code :");
    string intitule = dialogueDemandeTexte("Nouvelle option", "Intitule :");
    float prix = dialogueDemandeFloat("Nouvelle option", "Prix :");

    try
    {
        Garage ::getInstance().ajouteOption(Option(code, intitule, prix));
        ajouteOptionDisponible(intitule, prix);
    }
    catch(OptionException o)
    {
        cout<<"Erreur : "<< o.getMessage()<<endl;
        
        dialogueErreur("OptionException",o.getMessage().c_str());
    }
    
    

    // TO DO (étape 9)
    // /!\ try catch pour qu elees valeurs encodées soit correcte OptionException-> OK
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterEmploye_triggered()
{
    // TO DO (étape 11)
    string nom = dialogueDemandeTexte("Nouvel employé(e)", "Nom : ");
    string prenom = dialogueDemandeTexte("Nouvel employé(e)", "Prenom : ");
    string login = dialogueDemandeTexte("Nouvel employé(e)", "Login : ");
    string fonction = dialogueDemandeTexte("Nouvel employé(e)", "Fonction :");

    if ((nom == "" || prenom == "" || login == "") && (fonction != "Vendeur" || fonction != "Administratif"))
        dialogueErreur("Nouvel employé(e)", "Problème d'encodage");
    
    else 
    {
        Garage :: getInstance().ajouteEmploye(nom, prenom, login, fonction);

        
        videTableEmployes();
        Vecteur<Employe> tmp = Garage::getInstance().getEmployes();
        Iterateur<Employe> ite(tmp);
        ite.reset();
        
        int i = 0;

        while (!ite.end())
        {
            ajouteTupleTableEmployes(tmp[i].Tuple());
            i++;
            ite++;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_par_numero_triggered()
{
    // TO DO (étape 11)
    int i = dialogueDemandeInt("Employé", "Numéro : ");
    
    if (i > -1)
    {
        Garage :: getInstance().supprimeEmployeParNumero(i);
        
        videTableEmployes();
        Vecteur<Employe> tmp = Garage::getInstance().getEmployes();
        Iterateur<Employe> ite(tmp);
        ite.reset();
        
        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableEmployes(tmp[j].Tuple());
            j++;
            ite++;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerEmploye_selection_triggered()
{
    // TO DO (étape 11)
    int j = getIndiceEmployeSelectionne();

    if (j==-1)
        dialogueErreur("Erreur", "Pas d'employé selectionné");
    else
    {
        Garage::getInstance().supprimeEmployeParIndice(j);
    
        videTableEmployes();
        Vecteur<Employe> tmp = Garage::getInstance().getEmployes();
        Iterateur<Employe> ite(tmp);
        ite.reset();
        
        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableEmployes(tmp[j].Tuple());
            j++;
            ite++;
        }
    }   
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionAjouterClient_triggered()
{
    // TO DO (étape 11)
    string nom = dialogueDemandeTexte("Nouvel Client(e)", "Nom : ");
    string prenom = dialogueDemandeTexte("Nouvel Client(e)", "Prenom : ");
    string gsm = dialogueDemandeTexte("Nouvel Client(e)", "Gsm :");

    if ((nom == "" || prenom == "" || gsm == ""))
        dialogueErreur("Nouveau client(e)", "Problème d'encodage");
    
    else 
    {
        Garage :: getInstance().ajouteClient(nom, prenom, gsm);

        
        videTableClients();
        Vecteur<Client> tmp = Garage::getInstance().getClients();
        Iterateur<Client> ite(tmp);
        ite.reset();
        
        int i = 0;

        while (!ite.end())
        {
            ajouteTupleTableClients(tmp[i].Tuple());
            i++;
            ite++;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_par_numero_triggered()
{
    // TO DO (étape 11)
    int i = dialogueDemandeInt("Client", "Numéro : ");
    if (i > -1)
    {
        Garage :: getInstance().supprimeClientParNumero(i);
    
        videTableClients();
        Vecteur<Client> tmp = Garage::getInstance().getClients();
        Iterateur<Client> ite(tmp);
        ite.reset();
        
        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableClients(tmp[j].Tuple());
            j++;
            ite++;
        }

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionSupprimerClient_selection_triggered()
{
    // TO DO (étape 11)
    int j = getIndiceClientSelectionne();

    if (j==-1)
        dialogueErreur("Erreur", "Pas de client selectionné");
    else
    {
        Garage::getInstance().supprimeClientParIndice(j);
    
        videTableClients();
        Vecteur<Client> tmp = Garage::getInstance().getClients();
        Iterateur<Client> ite(tmp);
        ite.reset();
        
        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableClients(tmp[j].Tuple());
            j++;
            ite++;
        }
    }   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogin_triggered()
{
    // TO DO (étape 11)
    string mdp, mdpTemp;
    string login = dialogueDemandeTexte("Nouvel employé(e)", "Login : ");

    Vecteur<Employe> &tmp = Garage::getInstance().getEmployes();
    Iterateur<Employe> ite(tmp);
    ite.reset();
        
    int j = 0;

    while (!ite.end() && tmp[j].getLogin() != login)
    {
        j++;
        ite++;
    }

    if(ite.end())
        dialogueErreur("Erreur", "Login introuvable");
    else
    {

        mdp = dialogueDemandeTexte("Login", "Entrez un mot de passe : ");
        Garage::getInstance().pE = &tmp[j];

        try
        {
            mdpTemp = Garage :: getInstance().pE->getMotDePasse();
        }
        catch (PasswordException &p)
        {
            try
            {
                Garage :: getInstance().pE->setMotDePasse(mdp);   
                mdpTemp = mdp; 
            }
            catch (PasswordException &o)
            {
                dialogueErreur("Login", o.getMessage().c_str());
                return;
            }
            
        }
        
        
        if (mdp == mdpTemp)
        {
            if(Garage::getInstance().pE->getFonction() == "Vendeur")
            {
                setRole(2);
                setTitre(Garage::getInstance().pE->getFonction());
            }
            else if(Garage::getInstance().pE->getFonction() == "Administratif")
            {
                setRole(1);
                setTitre(Garage::getInstance().pE->getFonction());
            }
        }
        else
        {
            dialogueErreur("Login", "Mauvais Mot de passe !");
        }
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionLogout_triggered()
{
    // TO DO (étape 11)
    setTitre("");
    setRole(0);
    Garage ::getInstance().pE = NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_actionReset_Mot_de_passe_triggered()
{
    // TO DO (étape 11)
    Garage :: getInstance().pE->ResetMotDePasse();
    
    dialogueMessage("Employe", "Reset du message");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonChoisirModele_clicked()
{
    // TO DO (étape 9)
    Modele m;
    cout << "Clic sur le bouton choisir modele " << endl;
    int ind = getIndiceModeleSelectionneCombobox();
    if (ind == -1)
        dialogueErreur("Indice = -1", "Modele introuvable !");
    else
    {
        Garage ::getProjetEnCours().setModele(Garage ::getInstance().getModele(ind));
        m = Garage ::getInstance().getModele(ind);
        setModele(m.getNom(), m.getPuissance(), m.getMoteur(), m.getPrixDeBase(), m.getImage()); // ATTENTION : image pas fix
        setPrix(Garage ::getProjetEnCours().getPrix());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonAjouterOption_clicked()
{
    // TO DO (étape 9)
    Option o;
    cout << "Clic sur le bouton ajouter option" << endl;

    int ind = getIndiceOptionSelectionneeCombobox();
    if (ind == -1)
        dialogueErreur("Indice = -1", "Option introuvable ! ");
    else
    {
        // Cherche la première case vide et insere la nouvelle option
        int elem = 0;

        while (ui->tableWidgetOptions->item(elem, 0)!= NULL && ui->tableWidgetOptions->item(elem, 0)->text() != "") {
            elem++;
            qDebug() << ui->comboBoxOptionsDisponibles->itemText(elem);
        }
        
		
        cout << "elem : " << elem << endl;
        o = Garage ::getInstance().getOption(ind);
        Garage ::getProjetEnCours().AjouteOption(o);
        setTableOption(elem, o.getCode(), o.getIntitule(), o.getPrix());
        setPrix(Garage ::getProjetEnCours().getPrix());
        
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerOption_clicked()
{
    // TO DO (étape 9)
    Option *o;
    Voiture v;
    cout << "Clic sur le bouton supprimer option" << endl;

    int ind = getIndiceOptionSelectionneeTable();
	cout<<"ind : "<<ind<<endl;
    if (ind == -1 || ui->tableWidgetOptions->item(ind, 0) == NULL ||  (ui->tableWidgetOptions->item(ind, 0) != NULL && ui->tableWidgetOptions->item(ind, 0)->text() == ""))
        dialogueErreur("Indice = -1", "Option introuvable ! ");
    else
    {
        v = Garage ::getProjetEnCours();
        o = v[ind];
        Garage ::getProjetEnCours().RetireOption(o->getCode());
        Garage::getProjetEnCours().Affiche();
        setTableOption(ind, "", "", -1);
        setPrix(Garage ::getProjetEnCours().getPrix());
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonReduction_clicked()
{
    // TO DO (étape 9)
    Option *o;
    o = new Option[1];
    Option o1;
    Voiture v;
    cout << "Clic sur le bouton reduction" << endl;

    int ind = getIndiceOptionSelectionneeTable();
    if (ind == -1)
        dialogueErreur("Indice = -1", "Option introuvable ! ");
    else
    {
        v = Garage ::getProjetEnCours();
        o = v[ind];
        Garage ::getProjetEnCours().RetireOption(o->getCode());
        cout <<"Je suis apres le retireOption"<<endl;
        o1 = *o;
        try
        {
            o1--;
            Garage ::getProjetEnCours().AjouteOption(o1);
            cout << "Je suis apres le ajouteOption" << endl;
            setPrix(Garage ::getProjetEnCours().getPrix());

        }
        catch (OptionException o)
        {
            dialogueErreur("Option", o.getMessage().c_str());
        }
        

    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonEnregistrerProjet_clicked()
{
    // TO DO (étape 9)

    string nom = getNomProjetEnCours();

    Garage ::getProjetEnCours().setNom(nom);
    cout << "Nom : " << nom << endl;
    Garage ::getProjetEnCours().Save();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonOuvrirProjet_clicked()
{
    // TO DO (étape 9)

    Garage ::resetProjetEnCours();
    setModele("", 0, 0, 0, "");
    videTableOption();
    Modele m;
    Option *opt;
    string nom = getNomProjetEnCours();

    string nf = nom + ".car";
    Garage ::getProjetEnCours().Load(nf);
    m = Garage ::getProjetEnCours().getModele();
    setModele(m.getNom(), m.getPuissance(), m.getMoteur(), m.getPrixDeBase(), m.getImage()); // ATTENTION : image s'affiche pas

	int i = 0;
	while((opt = Garage :: getProjetEnCours()[i]) != NULL && i < 5)
    {
		setTableOption(i, opt->getCode(), opt->getIntitule(), opt->getPrix());
		i++;
	}
    setPrix(Garage :: getProjetEnCours().getPrix());
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauProjet_clicked()
{
    // TO DO (étape 9)
    Garage ::resetProjetEnCours();
    setModele("", 0, 0, 0, "");
    videTableOption();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonNouveauContrat_clicked()
{
    // TO DO (étape 13)

    int j = getIndiceClientSelectionne();
    if (j > -1)
    {

        int num = Contrat :: numContrat;
        Employe *ptr = Garage::getInstance().pE;
        Client &pC = Garage :: getInstance().getClients()[j];
        Contrat cont(num, ptr, &pC, getNomProjetEnCours());

        ajouteTupleTableContrats(cont.Tupple());
        Garage::getInstance().ajouteContrat(num, ptr, &pC, getNomProjetEnCours());

        videTableContrats();
        Vecteur<Contrat> tmp = Garage::getInstance().getContrat();
        Iterateur<Contrat> ite(tmp);
        ite.reset();

        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableContrats(tmp[j].Tupple());
            j++;
            ite++;
        }

    }
    else
    {
        dialogueErreur("Contrat", "vous devez selectionne un client !");
    }
    

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonSupprimerContrat_clicked()
{
    // TO DO (étape 13)

    int i = getIndiceContratSelectionne();
    if(i<0)
        dialogueErreur("Contrat", "Contrat non selectionné");
    else
    {
        Garage ::getInstance().supprimeContratParIndice(i);
        
        videTableContrats();
        Vecteur<Contrat> tmp = Garage::getInstance().getContrat();
        Iterateur<Contrat> ite(tmp);
        ite.reset();

        int j = 0;

        while (!ite.end())
        {
            ajouteTupleTableContrats(tmp[j].Tupple());
            j++;
            ite++;
        }
    }
    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ApplicGarageWindow::on_pushButtonVisualiserVoiture_clicked()
{
    // TO DO (étape 13)
    Option *opt;
    int i = getIndiceContratSelectionne();
    if (i < 0)
    {
        dialogueErreur("Contrat", "Contrat non selectionné");
    }
    else {
        Contrat cont = Garage :: getInstance().getContrat()[i];
        string nom = cont.getNomprojet() + ".car";
        Garage ::resetProjetEnCours();
        setModele("", 0, 0, 0, "");
        videTableOption();
        Garage :: getProjetEnCours().Load(nom);
        Modele m = Garage ::getProjetEnCours().getModele();
        setModele(m.getNom(), m.getPuissance(), m.getMoteur(), m.getPrixDeBase(), m.getImage()); // ATTENTION : image s'affiche pas

        int i = 0;
        while((opt = Garage :: getProjetEnCours()[i]) != NULL && i<5)
        {
            setTableOption(i, opt->getCode(), opt->getIntitule(), opt->getPrix());
            i++;
        }
        setPrix(Garage :: getProjetEnCours().getPrix());
        setNomProjetEnCours(cont.getNomprojet());
    }

}
