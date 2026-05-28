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
#include <QPixmap>
#include "settings.h"
#include "settingsdialog.h"

// ... (diğer kodlar aynı, sadece icon kısmını değiştiriyorum)

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Alirar");
    
    // DOĞRUDAN DOSYA YOLU İLE İKON AYARLA
    QPixmap pixmap("/home/ali/Alirar/alirar_256.png");
    if (!pixmap.isNull()) {
        QIcon icon(pixmap);
        app.setWindowIcon(icon);
    }
    
    QMainWindow window;
    if (!pixmap.isNull()) {
        window.setWindowIcon(QIcon(pixmap));
    }
    
    // ... devamı aynı
