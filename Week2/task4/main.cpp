#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Set the input file name
    QString inputFileName = "C:/Users/Johanna/Documents/secureprog/Week2/task3/random_data.bin";

    QFile inputFile(inputFileName);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open the file for reading";
        return 1;
    }

    // Read the content of the file
    QTextStream in(&inputFile);
    QString fileContent = in.readAll();

    // Filter out characters except letters, numbers, commas, and hyphens
    QString filteredContent;
    for (const QChar &ch : fileContent) {
        // Check if the character is one of the allowed characters
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == ',' || ch == '-') {
            filteredContent.append(ch);
        }
    }

    // Print the filtered content
    qDebug() << "Filtered Content:";
    qDebug().noquote() << filteredContent;

    return a.exec();
}
