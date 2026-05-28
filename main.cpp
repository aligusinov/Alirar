#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QDir>
#include <QLineEdit>
#include <QListWidget>
#include <QStatusBar>
#include <QDesktopServices>
#include <QUrl>
#include <QIcon>
#include <QTextEdit>
#include <QCheckBox>
#include <QDialog>
#include "settings.h"
#include "settingsdialog.h"

// Dil metinleri
QString tr(const QString &key) {
    QString lang = Settings::getLanguage();
    if (lang == "tr") {
        if (key == "title") return "ALİRAR";
        if (key == "subtitle") return "⚡ Modern RAR Arşiv Yöneticisi";
        if (key == "select") return "📂 RAR Arşivi Seç";
        if (key == "extract") return "📤 Çıkar";
        if (key == "about") return "ℹ️ Hakkında";
        if (key == "settings") return "⚙️ Ayarlar";
        if (key == "placeholder") return "Henüz dosya seçilmedi...";
        if (key == "scanning") return "⏳ RAR içeriği taranıyor...";
        if (key == "empty") return "📁 Arşiv içinde dosya bulunamadı";
        if (key == "error") return "❌ RAR içeriği okunamadı!";
        if (key == "selected") return "RAR dosyası seçildi!";
        if (key == "warning") return "Önce bir RAR dosyası seçin!";
        if (key == "extracting") return "⏳ Dosyalar çıkarılıyor...";
        if (key == "success") return "✅ Çıkarma tamamlandı!";
        if (key == "extract_success") return "Dosyalar çıkarıldı!";
        if (key == "extract_fail") return "Çıkarma başarısız!";
        if (key == "ready") return "✅ Alirar hazır";
        if (key == "about_title") return "Alirar Hakkında";
        if (key == "about_text") return "<h2>ALİRAR 1.0</h2><p>Modern RAR Arşiv Yöneticisi</p><p>WinRAR'dan daha modern, üstelik bedava!</p>";
    } else if (lang == "de") {
        if (key == "title") return "ALİRAR";
        if (key == "subtitle") return "⚡ Moderner RAR-Archiv-Manager";
        if (key == "select") return "📂 RAR-Archiv auswählen";
        if (key == "extract") return "📤 Extrahieren";
        if (key == "about") return "ℹ️ Über";
        if (key == "settings") return "⚙️ Einstellungen";
        if (key == "placeholder") return "Keine Datei ausgewählt...";
        if (key == "scanning") return "⏳ RAR-Inhalt wird gescannt...";
        if (key == "empty") return "📁 Archiv ist leer";
        if (key == "error") return "❌ RAR-Inhalt kann nicht gelesen werden!";
        if (key == "selected") return "RAR-Datei ausgewählt!";
        if (key == "warning") return "Bitte wählen Sie zuerst eine RAR-Datei!";
        if (key == "extracting") return "⏳ Dateien werden extrahiert...";
        if (key == "success") return "✅ Extraktion abgeschlossen!";
        if (key == "extract_success") return "Dateien extrahiert!";
        if (key == "extract_fail") return "Extraktion fehlgeschlagen!";
        if (key == "ready") return "✅ Alirar bereit";
        if (key == "about_title") return "Über Alirar";
        if (key == "about_text") return "<h2>ALİRAR 1.0</h2><p>Moderner RAR-Archiv-Manager</p><p>Moderner als WinRAR und kostenlos!</p>";
    } else {
        if (key == "title") return "ALİRAR";
        if (key == "subtitle") return "⚡ Modern RAR Archive Manager";
        if (key == "select") return "📂 Select RAR Archive";
        if (key == "extract") return "📤 Extract";
        if (key == "about") return "ℹ️ About";
        if (key == "settings") return "⚙️ Settings";
        if (key == "placeholder") return "No file selected...";
        if (key == "scanning") return "⏳ Scanning RAR contents...";
        if (key == "empty") return "📁 Archive is empty";
        if (key == "error") return "❌ Cannot read RAR contents!";
        if (key == "selected") return "RAR file selected!";
        if (key == "warning") return "Please select a RAR file first!";
        if (key == "extracting") return "⏳ Extracting files...";
        if (key == "success") return "✅ Extraction completed!";
        if (key == "extract_success") return "Files extracted!";
        if (key == "extract_fail") return "Extraction failed!";
        if (key == "ready") return "✅ Alirar ready";
        if (key == "about_title") return "About Alirar";
        if (key == "about_text") return "<h2>ALİRAR 1.0</h2><p>Modern RAR Archive Manager</p><p>More modern than WinRAR, completely free!</p>";
    }
    return key;
}

// Hoşgeldin / Şartlar penceresi
bool showWelcomeDialog() {
    if (Settings::hasAcceptedTerms()) return true;
    
    QDialog dialog;
    dialog.setWindowTitle("Alirar - Hoş Geldiniz");
    dialog.setModal(true);
    dialog.setMinimumWidth(500);
    dialog.setMinimumHeight(450);
    
    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    
    QLabel *logo = new QLabel;
    logo->setAlignment(Qt::AlignCenter);
    logo->setText("<h1 style='color:#2ecc71;'>ALİRAR</h1>");
    layout->addWidget(logo);
    
    QLabel *title = new QLabel("<b>Hoş Geldiniz!</b>");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    
    // Dil seçimi
    QLabel *langLabel = new QLabel("Dil Seçiniz / Select Language:");
    layout->addWidget(langLabel);
    
    QComboBox *langCombo = new QComboBox;
    langCombo->addItem("🇹🇷 Türkçe", "tr");
    langCombo->addItem("🇬🇧 English", "en");
    langCombo->addItem("🇩🇪 Deutsch", "de");
    layout->addWidget(langCombo);
    
    // Şartlar
    QTextEdit *termsText = new QTextEdit;
    termsText->setReadOnly(true);
    termsText->setPlainText(
        "KULLANIM ŞARTLARI / TERMS OF USE\n\n"
        "1. Alirar tamamen ücretsiz bir yazılımdır.\n"
        "2. Herhangi bir amaç için kullanılabilir.\n"
        "3. Kopyalanabilir, dağıtılabilir.\n"
        "4. Garanti verilmez, sorumluluk kullanıcıya aittir.\n"
        "5. WinRAR'dan daha modern, üstelik bedava!\n\n"
        "Devam etmek için kabul edin."
    );
    termsText->setMinimumHeight(150);
    layout->addWidget(termsText);
    
    QCheckBox *acceptCheck = new QCheckBox("Kullanım şartlarını kabul ediyorum");
    layout->addWidget(acceptCheck);
    
    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *acceptBtn = new QPushButton("Kabul Et");
    QPushButton *exitBtn = new QPushButton("Çıkış");
    btnLayout->addWidget(acceptBtn);
    btnLayout->addWidget(exitBtn);
    layout->addLayout(btnLayout);
    
    bool accepted = false;
    QObject::connect(acceptBtn, &QPushButton::clicked, [&]() {
        if (acceptCheck->isChecked()) {
            Settings::setLanguage(langCombo->currentData().toString());
            Settings::setTermsAccepted(true);
            accepted = true;
            dialog.accept();
        } else {
            QMessageBox::warning(&dialog, "Uyarı", "Lütfen kullanım şartlarını kabul edin!");
        }
    });
    
    QObject::connect(exitBtn, &QPushButton::clicked, [&]() {
        dialog.reject();
    });
    
    dialog.exec();
    return accepted;
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Alirar");
    
    // İlk açılışta şartlar
    if (!showWelcomeDialog()) {
        return 0;
    }
    
    QMainWindow window;
    QWidget *central = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    
    // Başlık
    QLabel *titleLabel = new QLabel;
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setText("<h1 style='color:#2ecc71;'>" + tr("title") + "</h1>"
                       "<p style='color:#3498db;'>" + tr("subtitle") + "</p>");
    layout->addWidget(titleLabel);
    
    // Seçili dosya
    QLineEdit *selectedFile = new QLineEdit;
    selectedFile->setPlaceholderText(tr("placeholder"));
    selectedFile->setReadOnly(true);
    layout->addWidget(selectedFile);
    
    // Dosya listesi
    QListWidget *fileList = new QListWidget;
    layout->addWidget(fileList);
    
    QString currentArchive;
    
    // Butonlar
    QPushButton *openBtn = new QPushButton(tr("select"));
    QPushButton *extractBtn = new QPushButton(tr("extract"));
    QPushButton *aboutBtn = new QPushButton(tr("about"));
    QPushButton *settingsBtn = new QPushButton(tr("settings"));
    
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(openBtn);
    btnLayout->addWidget(extractBtn);
    btnLayout->addWidget(aboutBtn);
    btnLayout->addWidget(settingsBtn);
    layout->addLayout(btnLayout);
    
    // Durum çubuğu
    QStatusBar *statusBar = new QStatusBar;
    statusBar->showMessage(tr("ready"));
    layout->addWidget(statusBar);
    
    // Tema uygulama fonksiyonu
    auto applyTheme = [&]() {
        if (Settings::getDarkTheme()) {
            window.setStyleSheet("QMainWindow { background-color: #1a1a2e; }"
                                "QLineEdit { background-color: #2d2d2d; color: #2ecc71; }"
                                "QListWidget { background-color: #1e1e2e; color: #ccc; }"
                                "QPushButton { background-color: #2c3e50; color: white; border-radius: 5px; padding: 8px; }");
        } else {
            window.setStyleSheet("QMainWindow { background-color: #f0f0f0; }"
                                "QLineEdit { background-color: white; color: black; }"
                                "QListWidget { background-color: white; color: black; }"
                                "QPushButton { background-color: #3498db; color: white; border-radius: 5px; padding: 8px; }");
        }
    };
    
    // Metin güncelleme
    auto updateTexts = [&]() {
        titleLabel->setText("<h1 style='color:#2ecc71;'>" + tr("title") + "</h1>"
                           "<p style='color:#3498db;'>" + tr("subtitle") + "</p>");
        openBtn->setText(tr("select"));
        extractBtn->setText(tr("extract"));
        aboutBtn->setText(tr("about"));
        settingsBtn->setText(tr("settings"));
        selectedFile->setPlaceholderText(tr("placeholder"));
        statusBar->showMessage(tr("ready"));
        window.setWindowTitle(tr("title") + " - " + tr("subtitle"));
    };
    
    // Arşiv aç
    QObject::connect(openBtn, &QPushButton::clicked, [&]() {
        QString downloads = QDir::homePath() + "/İndirilenler";
        if (!QDir(downloads).exists()) downloads = QDir::homePath() + "/Downloads";
        
        QString filename = QFileDialog::getOpenFileName(&window, tr("select"), downloads, "RAR Dosyası (*.rar *.RAR)");
        if (!filename.isEmpty()) {
            currentArchive = filename;
            selectedFile->setText("📦 " + filename);
            
            fileList->clear();
            fileList->addItem(tr("scanning"));
            
            QProcess *process = new QProcess;
            QObject::connect(process, &QProcess::finished, [process, fileList](int code) {
                if (code == 0) {
                    QString output = process->readAllStandardOutput();
                    QStringList lines = output.split('\n');
                    fileList->clear();
                    int count = 0;
                    for (QString line : lines) {
                        line = line.trimmed();
                        if (!line.isEmpty() && !line.startsWith("----") && !line.startsWith("RAR")) {
                            fileList->addItem("📄 " + line);
                            count++;
                        }
                    }
                    if (count == 0) fileList->addItem(tr("empty"));
                } else {
                    fileList->clear();
                    fileList->addItem(tr("error"));
                }
                process->deleteLater();
            });
            process->start("unrar", QStringList() << "lb" << filename);
        }
    });
    
    // Çıkar
    QObject::connect(extractBtn, &QPushButton::clicked, [&]() {
        if (currentArchive.isEmpty()) {
            QMessageBox::warning(&window, tr("title"), tr("warning"));
            return;
        }
        
        QString destDir = QFileDialog::getExistingDirectory(&window, tr("extract"), QDir::homePath());
        if (destDir.isEmpty()) return;
        
        fileList->clear();
        fileList->addItem(tr("extracting"));
        
        QProcess *process = new QProcess;
        QObject::connect(process, &QProcess::finished, [process, destDir, fileList](int code) {
            if (code == 0) {
                fileList->clear();
                fileList->addItem(tr("success"));
                fileList->addItem("📁 " + destDir);
                QMessageBox::information(nullptr, tr("title"), tr("extract_success"));
                if (Settings::getAutoOpenFolder()) {
                    QDesktopServices::openUrl(QUrl::fromLocalFile(destDir));
                }
            } else {
                fileList->clear();
                fileList->addItem(tr("extract_fail"));
            }
            process->deleteLater();
        });
        process->start("unrar", QStringList() << "x" << currentArchive << destDir + "/");
    });
    
    // Hakkında
    QObject::connect(aboutBtn, &QPushButton::clicked, [&]() {
        QMessageBox::about(&window, tr("about_title"), tr("about_text"));
    });
    
    // Ayarlar
    QObject::connect(settingsBtn, &QPushButton::clicked, [&]() {
        SettingsDialog dialog(&window);
        if (dialog.exec() == QDialog::Accepted) {
            updateTexts();
            applyTheme();
        }
    });
    
    central->setLayout(layout);
    window.setCentralWidget(central);
    window.resize(950, 650);
    window.setWindowTitle(tr("title") + " - " + tr("subtitle"));
    
    applyTheme();
    window.show();
    
    return app.exec();
}
