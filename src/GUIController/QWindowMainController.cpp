/*
 * QWindowMainController.cpp
 *
 *  Created on: 9 juin 2016
 *      Author: echopin
 */

#include "Database/DatabaseController.h"

#include "GUI/QAboutDialog.h"
#include "GUI/QWindowMain.h"
#include "GUI/QDatabaseConnectionView.h"
#include "GUI/QDatabaseSelectionView.h"

#include "QWindowMainController.h"
#include "QDatabaseConnectionViewController.h"
#include "QDatabaseSelectionViewController.h"

QWindowMainController::QWindowMainController()
{
	m_pMainWindow = NULL;
}

QWindowMainController::~QWindowMainController()
{

}

void QWindowMainController::init(QWindowMain* pMainWindow)
{
	m_pMainWindow = pMainWindow;

    connect(m_pMainWindow->getNewConnectionAction(), SIGNAL(triggered()), this, SLOT(newDatabaseConnection()));
    connect(m_pMainWindow->getQuitAction(), SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_pMainWindow->getAboutAction(), SIGNAL(triggered()), this, SLOT(about()));
    connect(m_pMainWindow->getDatabaseConnectionTab(), SIGNAL(tabCloseRequested(int)), this, SLOT(closeConnectionTab(int)));

    newDatabaseConnection();
}

void QWindowMainController::newDatabaseConnection()
{
	QDatabaseSelectionView* pSelectionView = new QDatabaseSelectionView(m_pMainWindow);
	QDatabaseSelectionViewController* pSelectionViewController = new QDatabaseSelectionViewController();
	pSelectionViewController->init(m_pMainWindow, pSelectionView);
	pSelectionView->exec();
}

void QWindowMainController::about()
{
	QAboutDialog aboutDialog(m_pMainWindow);
	aboutDialog.exec();
}

void QWindowMainController::closeConnectionTab(const int& index)
{
	QWidget* tabItem = m_pMainWindow->getDatabaseConnectionTab()->widget(index);
	m_pMainWindow->getDatabaseConnectionTab()->removeTab(index);

	delete(tabItem);
}
