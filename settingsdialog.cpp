#include "settingsdialog.h"
#include "settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QApplication>
#include <QProcess>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Ayarlar / Settings");
    setModal(true);
    setMinimumWidth(450);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Dil Grubu
    QGroupBox *langGroup = new QGroupBox("🌍 Dil / Language");
    QVBoxLayout *langLayout = new QVBoxLayout;
    languageCombo = new QComboBox;
    languageCombo->addItem("🇹🇷 Türkçe", "tr");
    languageCombo->addItem("🇬🇧 English", "en");
    languageCombo->addItem("🇩🇪 Deutsch", "de");
    langLayout->addWidget(languageCombo);
    langGroup->setLayout(langLayout);
    mainLayout->addWidget(langGroup);
    
    // Görünüm Grubu
    QGroupBox *themeGroup = new QGroupBox("🎨 Görünüm / Theme");
    QVBoxLayout *themeLayout = new QVBoxLayout;
    darkThemeCheck = new QCheckBox("🌙 Koyu Tema / Dark Theme");
    themeLayout->addWidget(darkThemeCheck);
    themeGroup->setLayout(themeLayout);
    mainLayout->addWidget(themeGroup);
    
    // Çıkarma Grubu
    QGroupBox *extractGroup = new QGroupBox("📤 Çıkarma / Extraction");
    QVBoxLayout *extractLayout = new QVBoxLayout;
    autoOpenCheck = new QCheckBox("📂 Çıkarma sonrası klasörü aç / Open folder after extract");
    extractLayout->addWidget(autoOpenCheck);
    extractGroup->setLayout(extractLayout);
    mainLayout->addWidget(extractGroup);
    
    // Bilgi
    infoLabel = new QLabel;
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("color: #f39c12; font-size: 11px; padding: 10px;");
    infoLabel->setText("💡 İpucu: Dil değiştirdiğinizde uygulama yeniden başlatılacaktır.");
    mainLayout->addWidget(infoLabel);
    
    // Butonlar
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *saveBtn = new QPushButton("💾 Kaydet / Save");
    QPushButton *cancelBtn = new QPushButton("❌ İptal / Cancel");
    saveBtn->setStyleSheet("QPushButton { padding: 10px; background: #2c3e50; color: white; border-radius: 5px; }");
    cancelBtn->setStyleSheet("QPushButton { padding: 10px; background: #2c3e50; color: white; border-radius: 5px; }");
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);
    
    connect(saveBtn, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    connect(cancelBtn, &QPushButton::clicked, this, &SettingsDialog::cancelSettings);
    
    loadSettings();
}

void SettingsDialog::loadSettings() {
    int idx = languageCombo->findData(Settings::getLanguage());
    if (idx >= 0) languageCombo->setCurrentIndex(idx);
    darkThemeCheck->setChecked(Settings::getDarkTheme());
    autoOpenCheck->setChecked(Settings::getAutoOpenFolder());
}

void SettingsDialog::saveSettings() {
    QString oldLang = Settings::getLanguage();
    QString newLang = languageCombo->currentData().toString();
    
    Settings::setLanguage(newLang);
    Settings::setDarkTheme(darkThemeCheck->isChecked());
    Settings::setAutoOpenFolder(autoOpenCheck->isChecked());
    
    QMessageBox::information(this, "Başarılı", "Ayarlar kaydedildi!\nSettings saved!");
    
    if (oldLang != newLang) {
        QMessageBox::information(this, "Yeniden Başlat", "Dil değişti. Uygulama yeniden başlatılacak.");
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    accept();
}

void SettingsDialog::cancelSettings() {
    reject();
}
