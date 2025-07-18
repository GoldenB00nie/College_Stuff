import findGooglePlayApp
import googlePlayAppScraper
import categorizeCommentsToCSV

if __name__ == "__main__":
    aplicativos = ["penguin isle"]

    nameToSearch = "canva"
    for nameToSearch in aplicativos:
        appId = findGooglePlayApp.searchAppId(nameToSearch)
        caminho = googlePlayAppScraper.coletarComentarios(appId)
        categorizeCommentsToCSV.categorizeToCSV(caminho, appId)
