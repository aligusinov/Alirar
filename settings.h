#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QSettings>

class Settings {
public:
    static QString getLanguage() {
        QSettings s("Alirar", "Alirar");
        return s.value("language", "tr").toString();
    }
    static void setLanguage(const QString &lang) {
        QSettings s("Alirar", "Alirar");
        s.setValue("language", lang);
    }
    
    static bool getDarkTheme() {
        QSettings s("Alirar", "Alirar");
        return s.value("darkTheme", true).toBool();
    }
    static void setDarkTheme(bool enabled) {
        QSettings s("Alirar", "Alirar");
        s.setValue("darkTheme", enabled);
    }
    
    static bool getAutoOpenFolder() {
        QSettings s("Alirar", "Alirar");
        return s.value("autoOpenFolder", true).toBool();
    }
    static void setAutoOpenFolder(bool enabled) {
        QSettings s("Alirar", "Alirar");
        s.setValue("autoOpenFolder", enabled);
    }
    
    static bool hasAcceptedTerms() {
        QSettings s("Alirar", "Alirar");
        return s.value("termsAccepted", false).toBool();
    }
    static void setTermsAccepted(bool accepted) {
        QSettings s("Alirar", "Alirar");
        s.setValue("termsAccepted", accepted);
    }
};

#endif
