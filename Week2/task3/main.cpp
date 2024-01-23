#include <QCoreApplication>
#include <QFile>
#include <QCryptographicHash>
#include <QRandomGenerator>

void generateAndWriteRandomData(const QString &fileName, qint64 dataSize) {
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
        // Generate crypto-safe random data
        QByteArray randomData;
        randomData.resize(dataSize);
        for (qint64 i = 0; i < dataSize; ++i) {
            randomData[i] = QRandomGenerator::global()->generate();
        }

        // Calculate the hash of the random data (optional)
        QByteArray hash = QCryptographicHash::hash(randomData, QCryptographicHash::Sha256);

        // Write the random data to the file
        file.write(randomData);

        qDebug() << "Random data has been written to" << fileName;
        qDebug() << "Hash for it:" << hash.toHex();
    } else {
        qDebug() << "Error: Could not open the file for writing";
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // Set the file name and data size
    QString fileName = "C:/Users/Johanna/Documents/secureprog/Week2/task3/random_data.bin";
    qint64 dataSize = 1024; // Adjust the size as needed

    // Generate and write random data to the file
    generateAndWriteRandomData(fileName, dataSize);

    return a.exec();
}
