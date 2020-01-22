#include "Headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DatabaseInterface* db)
        : QMainWindow (parent)
        , ui (new Ui::MainWindow)
{
        try {
                ui->setupUi (this);
                if (db == nullptr) {
                        this->dbInterface = new DatabaseInterface ();
                }
                else{
                        this->dbInterface = db;
                }

                emit onUpdate ();
        } catch (QString exception) {
                throw QString (exception);
        }
}

MainWindow::~MainWindow()
{
        delete ui;
}

void MainWindow::login ()
{
        if (currentlyLoggedIn > 0) {
                initializeWidgetList ();
                this->view = new QListView ();
                dbInterface->getMappedWidget (this->mapper, widgets, this->type, currentlyLoggedIn);
                dbInterface->getView (ui->ProjektList, this->type, currentlyLoggedIn);
                dbInterface->getItemView (ui->ProjektTree, this->type, currentlyLoggedIn);
                setAppropriateWidgetsHidden ();
//                setAppropriateWidgetsEnabled ();
                setAppropriateWidgetsEnabled (&this->type);
        }
        else {
                return;
        }
}

QString MainWindow::getType () const
{
        return type;
}

void MainWindow::setType (const QString &value)
{
        type = value;
}

int MainWindow::getCurrentlyLoggedIn () const
{
        return currentlyLoggedIn;
}

void MainWindow::setCurrentlyLoggedIn (int value)
{
        currentlyLoggedIn = value;
}

void MainWindow::setAppropriateWidgetsHidden (const QModelIndex* index)
{
        if (index != nullptr)
                qDebug () << "MainWindow::setAppropriateWidgetsHidden(" << index->data ().toString ().split (":").at (0) << ")";
        if (index == nullptr) {
                for (int i = 0; i < widgets.length (); i++) {
                        widgets.at (i)->setHidden (true);
//                        qDebug () << widgets.at (i)->objectName () << " is set hidden.";
                }
        }
        else{
                QList<int> itemPos = dbInterface->getKEYS ().keys (index->data ().toString ().split (":").at (0));
                setAppropriateWidgetsHidden ();
                for (int i = 0; i < itemPos.length (); i++) {
                        switch (itemPos.at (i)) {
                        case 1:
                                setWidgetVisible (ui->label_1);
                                setWidgetVisible (ui->label_2);
                                setWidgetVisible (ui->label_3);
                                setWidgetVisible (ui->comboBox_1);
                                setWidgetVisible (ui->comboBox_2);
                                setWidgetVisible (ui->comboBox_3);
                                break;

                        case 2:
                                setWidgetVisible (ui->labelStatus);
                                setWidgetVisible (ui->statusCombo);
                                break;

                        case 3:
                                setWidgetVisible (ui->lineEdit_1);
                                break;

                        case 4:
                                setWidgetVisible (ui->textEdit_1);
                                break;

                        case 5:
                                setWidgetVisible (ui->textEdit_2);
                                break;

                        case 6:
                                setWidgetVisible (ui->labelOrg);
                                setWidgetVisible (ui->orgCombo);
                                break;

                        case 7:
                        case 8:
                                setWidgetVisible (ui->labelAnsprech);
                                setWidgetVisible (ui->ansprechCombo);
                                break;

                        case 9:
                        case 10:
                                setWidgetVisible (ui->labelDozent);
                                setWidgetVisible (ui->dozentCombo);
                                break;

                        default:
                                qDebug () << itemPos.at (i) << " not in List";
                                break;
                        }
                }
        }
}

void MainWindow::setAppropriateWidgetsEnabled (const QString* type)
{
        if (type == nullptr) {
                qDebug () << "setAppropriateWidgetsEnabled: type is a nullptr";
        }

        ui->lineEdit_1->setEnabled (true);
        ui->textEdit_1->setEnabled (true);
        ui->textEdit_2->setEnabled (true);
        ui->comboBox_1->setEnabled (true);
        ui->comboBox_2->setEnabled (true);
        ui->comboBox_3->setEnabled (true);
        ui->orgCombo->setEnabled (true);
        ui->ansprechCombo->setEnabled (true);
        ui->dozentCombo->setEnabled (true);
        ui->statusCombo->setEnabled (true);
        ui->actionGruppe->setEnabled (true);

        if (*type == "Dozent") {
                ui->lineEdit_1->setEnabled (false);
                ui->textEdit_1->setEnabled (false);
                ui->textEdit_2->setEnabled (false);
                ui->comboBox_1->setEnabled (false);
                ui->comboBox_2->setEnabled (false);
                ui->comboBox_3->setEnabled (false);
                ui->orgCombo->setEnabled (false);
                ui->ansprechCombo->setEnabled (false);
                ui->dozentCombo->setEnabled (false);
                ui->actionGruppe->setEnabled (false);
        }
        else if (*type == "Student") {
                ui->lineEdit_1->setEnabled (false);
                ui->textEdit_1->setEnabled (false);
                ui->textEdit_2->setEnabled (false);
                ui->comboBox_1->setEnabled (false);
                ui->comboBox_2->setEnabled (false);
                ui->comboBox_3->setEnabled (false);
                ui->orgCombo->setEnabled (true);
                ui->ansprechCombo->setEnabled (false);
                ui->dozentCombo->setEnabled (false);
                ui->statusCombo->setEnabled (false);
        }
        else if (*type == "Enabled") {
                ui->statusCombo->setEnabled (false);
        }
        else{
                qDebug () << "setAppropriateWidgetsEnabled(" << type << "): no such type";
        }
}

void MainWindow::initializeWidgetList ()
{
        this->mapper = new QDataWidgetMapper (this);

        widgets.append (ui->lineEdit_1);

        widgets.append (ui->textEdit_1);

        widgets.append (ui->textEdit_2);

        widgets.append (ui->label_1);
        ui->label_1->setBuddy (ui->comboBox_1);
        widgets.append (ui->comboBox_1);

        widgets.append (ui->label_2);
        ui->label_2->setBuddy (ui->comboBox_2);
        widgets.append (ui->comboBox_2);

        widgets.append (ui->label_3);
        ui->label_3->setBuddy (ui->comboBox_3);
        widgets.append (ui->comboBox_3);

        widgets.append (ui->labelStatus);
        ui->labelStatus->setBuddy (ui->statusCombo);
        widgets.append (ui->statusCombo);

        widgets.append (ui->labelDozent);
        ui->labelDozent->setBuddy (ui->dozentCombo);
        widgets.append (ui->dozentCombo);

        widgets.append (ui->labelAnsprech);
        ui->labelAnsprech->setBuddy (ui->ansprechCombo);
        widgets.append (ui->ansprechCombo);

        widgets.append (ui->labelOrg);
        ui->labelOrg->setBuddy (ui->orgCombo);
        widgets.append (ui->orgCombo);
}

void MainWindow::setWidgetVisible (QWidget* widget)
{
        widget->setHidden (false);
}

void MainWindow::on_actionLog_Out_triggered ()
{
        emit backToLogin ();
}

void MainWindow::on_actionGruppe_triggered ()
{
        InsertProjectDialog i (this, dbInterface);

//        i.showMaximized ();
        this->hide ();
        i.exec ();
        this->show ();
}

void MainWindow::on_actionOrganisation_triggered ()
{
        OrganisationScreen o (this, dbInterface);

//        o.showMaximized ();

        this->hide ();
        o.exec ();
        this->show ();
}

void MainWindow::on_login ()
{
        qDebug () << "on:login";
}



void MainWindow::on_ProjektList_activated (const QModelIndex &index)
{
        qDebug () << "MainWindow::on_ProjektList_activated(" << index.data () << ")";
        QModelIndex* i = new QModelIndex (index);

        dbInterface->setIndex (i);
}

void MainWindow::on_ProjektList_entered (const QModelIndex &index)
{
        qDebug () << "MainWindow::on_ProjektList_entered(" << index.data () << ")";
        QModelIndex* i = new QModelIndex (index);

        dbInterface->setIndex (i);
}

void MainWindow::on_ProjektList_clicked (const QModelIndex &index)
{
        qDebug () << "MainWindow::on_ProjektList_clicked(" << index.data () << ")";
        dbInterface->changeIndex (index);
        dbInterface->getItemView (ui->ProjektTree, this->type, currentlyLoggedIn);
}

void MainWindow::on_ProjektTree_clicked (const QModelIndex &index)
{
        setAppropriateWidgetsHidden (&index);
        ui->orgCombo->setCurrentIndex (dbInterface->getProjekte ()->at (dbInterface->getIndex ()->row ())->getForeignOrgKey ());
}

void MainWindow::on_ProjektTree_activated (const QModelIndex &index)
{
        setAppropriateWidgetsHidden (&index);
        ui->orgCombo->setCurrentIndex (dbInterface->getProjekte ()->at (dbInterface->getIndex ()->row ())->getForeignOrgKey ());
}

void MainWindow::on_ProjektTree_entered (const QModelIndex &index)
{
        setAppropriateWidgetsHidden (&index);
        ui->orgCombo->setCurrentIndex (dbInterface->getProjekte ()->at (dbInterface->getIndex ()->row ())->getForeignOrgKey ());
}

void MainWindow::on_statusCombo_currentIndexChanged (int index)
{
        qDebug () << dbInterface->getIndex ()->row ();
        for (int i = 0; i < dbInterface->getProjekte ()->length (); i++) {
                if (dbInterface->getIndex ()->row () + 1 == dbInterface->getProjekte ()->at (i)->getPrimaryKey ()) {
                        qDebug () << dbInterface->getProjekte ()->at (i)->getProjektName ();

                        dbInterface->getProjekte ()->at (i)->setStatus (index);
                        dbInterface->saveProjekte ();
                        dbInterface->loadProjekte ();
                }
        }
        ui->ProjektTree->update ();
        if (this->window ())
                window ()->update ();
        update ();
}

void MainWindow::on_orgCombo_currentIndexChanged (int index)
{
        qDebug () << dbInterface->getIndex ()->row ();
        for (int i = 0; i < dbInterface->getProjekte ()->length (); i++) {
                if (dbInterface->getIndex ()->row () + 1 == dbInterface->getProjekte ()->at (i)->getPrimaryKey ()) {
                        qDebug () << dbInterface->getProjekte ()->at (i)->getProjektName ();
                        dbInterface->getProjekte ()->at (i)->setForeignOrgKey (index);
                }
        }
}

void MainWindow::on_ansprechCombo_currentIndexChanged (int index)
{
        qDebug () << dbInterface->getIndex ()->row ();
        for (int i = 0; i < dbInterface->getProjekte ()->length (); i++) {
                if (dbInterface->getIndex ()->row () + 1 == dbInterface->getProjekte ()->at (i)->getPrimaryKey ()) {
                        qDebug () << dbInterface->getProjekte ()->at (i)->getProjektName ();
                        for (int j = 0; j < dbInterface->getAnsprechpartner ()->length (); j++) {
                                if (dbInterface->getProjekte ()->at (i)->getForeignOrgKey () == dbInterface->getAnsprechpartner ()->at (j)->getForeignKey ()) {
                                        dbInterface->getAnsprechpartner ()->at (j)->setForeignKey (index);
                                }
                        }
                }
        }
}

void MainWindow::on_dozentCombo_currentIndexChanged (int index)
{
        qDebug () << dbInterface->getIndex ()->row ();
        for (int i = 0; i < dbInterface->getProjekte ()->length (); i++) {
                if (dbInterface->getIndex ()->row () + 1 == dbInterface->getProjekte ()->at (i)->getPrimaryKey ()) {
                        qDebug () << dbInterface->getProjekte ()->at (i)->getProjektName ();
                        dbInterface->getProjekte ()->at (i)->setForeignDozKey (index);
                }
        }
}

void MainWindow::on_comboBox_3_currentIndexChanged (int index)
{
}

void MainWindow::on_comboBox_2_currentIndexChanged (int index)
{
}

void MainWindow::on_comboBox_1_currentIndexChanged (int index)
{
}

void MainWindow::on_textEdit_2_textChanged ()
{
}

void MainWindow::on_textEdit_1_textChanged ()
{
}

void MainWindow::on_lineEdit_1_editingFinished ()
{
}

