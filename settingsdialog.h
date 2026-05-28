#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);

private slots:
    void saveSettings();
    void cancelSettings();

private:
    QComboBox *languageCombo;
    QCheckBox *darkThemeCheck;
    QCheckBox *autoOpenCheck;
    QLabel *infoLabel;
    
    void loadSettings();
};

#endif
