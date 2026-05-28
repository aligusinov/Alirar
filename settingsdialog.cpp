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
    setWindowTitle("Alirar Ayarları");
    setModal(true);
    setMinimumWidth(450);
    setMinimumHeight(400);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Dil Ayarları
    QGroupBox *langGroup = new QGroupBox("🌍 Dil Seçeneği");
    QVBoxLayout *langLayout = new QVBoxLayout;
    
    QLabel *langLabel = new QLabel("Uygulama Dili:");
    languageCombo = new QComboBox;
    languageCombo->addItem("🇹🇷 Türkçe", "tr");
    languageCombo->addItem("🇬🇧 English", "en");
    languageCombo->addItem("🇩🇪 Deutsch", "de");
    
    langLayout->addWidget(langLabel);
    langLayout->addWidget(languageCombo);
    langGroup->setLayout(langLayout);
    mainLayout->addWidget(langGroup);
    
    // Görünüm Ayarları
    QGroupBox *themeGroup = new QGroupBox("🎨 Görünüm");
    QVBoxLayout *themeLayout = new QVBoxLayout;
    
    darkThemeCheck = new QCheckBox("🌙 Koyu Tema (Dark Theme)");
    themeLayout->addWidget(darkThemeCheck);
    themeGroup->setLayout(themeLayout);
    mainLayout->addWidget(themeGroup);
    
    // Çıkarma Ayarları
    QGroupBox *extractGroup = new QGroupBox("📤 Çıkarma Ayarları");
    QVBoxLayout *extractLayout = new QVBoxLayout;
    
    autoOpenCheck = new QCheckBox("📂 Çıkarma tamamlandığında klasörü otomatik aç");
    extractLayout->addWidget(autoOpenCheck);
    extractGroup->setLayout(extractLayout);
    mainLayout->addWidget(extractGroup);
    
    // Bilgi
    infoLabel = new QLabel;
    infoLabel->setWordWrap(true);
    infoLabel->setStyleSheet("QLabel { color: #f39c12; font-size: 11px; padding: 10px; }");
    infoLabel->setText("💡 İpucu: Dil değiştirdiğinizde uygulama yeniden başlatılacaktır.");
    mainLayout->addWidget(infoLabel);
    
    // Butonlar
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *saveBtn = new QPushButton("💾 Kaydet");
    QPushButton *cancelBtn = new QPushButton("❌ İptal");
    QString btnStyle = "QPushButton { padding: 10px 20px; border-radius: 5px; background-color: #2c3e50; color: white; }"
                       "QPushButton:hover { background-color: #34495e; }";
    saveBtn->setStyleSheet(btnStyle);
    cancelBtn->setStyleSheet(btnStyle);
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);
    
    connect(saveBtn, &QPushButton::clicked, this, &SettingsDialog::saveSettings);
    connect(cancelBtn, &QPushButton::clicked, this, &SettingsDialog::cancelSettings);
    
    loadSettings();
}

void SettingsDialog::loadSettings() {
    // Dil
    int idx = languageCombo->findData(Settings::getLanguage());
    if (idx >= 0) languageCombo->setCurrentIndex(idx);
    
    // Tema
    darkThemeCheck->setChecked(Settings::getDarkTheme());
    
    // Otomatik aç
    autoOpenCheck->setChecked(Settings::getAutoOpenFolder());
}

void SettingsDialog::saveSettings() {
    QString oldLang = Settings::getLanguage();
    QString newLang = languageCombo->currentData().toString();
    
    Settings::setLanguage(newLang);
    Settings::setDarkTheme(darkThemeCheck->isChecked());
    Settings::setAutoOpenFolder(autoOpenCheck->isChecked());
    
    QMessageBox::information(this, "Ayarlar Kaydedildi", 
        "✅ Ayarlar başarıyla kaydedildi!\n\n" +
        QString("Dil: %1\nTema: %2\nÇıkarma sonrası klasör açma: %3")
        .arg(languageCombo->currentText())
        .arg(darkThemeCheck->isChecked() ? "Koyu" : "Açık")
        .arg(autoOpenCheck->isChecked() ? "Aktif" : "Pasif"));
    
    if (oldLang != newLang) {
        QMessageBox::information(this, "Yeniden Başlatma Gerekli", 
            "Dil değiştirildiği için uygulama yeniden başlatılacak.");
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    
    accept();
}

void SettingsDialog::cancelSettings() {
    reject();
}
