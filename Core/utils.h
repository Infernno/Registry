#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFileInfo>
#include <QTableWidget>
#include <QHeaderView>
#include <QCryptographicHash>

typedef QVector<QTableWidgetItem*> TableRow;
typedef QVector<TableRow> TableData;


class Utils
{
public:
    Utils() = delete;

    static bool FileExists(const QString & path)
    {
        QFileInfo check_file(path);

        if (check_file.exists() && check_file.isFile())
        {
            return true;
        }

        return false;
    }

    static QString GetHash(const QString & input)
    {
        return QString(QCryptographicHash::hash(input.toUtf8(),QCryptographicHash::Md5).toHex());
    }

    static void ClearTable(QTableWidget * widget)
    {
        widget->model()->removeRows(0, widget->rowCount());
        //widget->clear();
        widget->clearContents();

    }

    static void InitializeTable(QTableWidget * widget, QStringList headers)
    {
        widget->setColumnCount(headers.size());
        widget->setSortingEnabled(true);
        widget->setShowGrid(true);
        widget->setSelectionMode(QAbstractItemView::SingleSelection);
        widget->setSelectionBehavior(QAbstractItemView::SelectRows);
        widget->setHorizontalHeaderLabels(headers);
        widget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }

    static void Update(QTableWidget * widget, const QVector<QVector<QTableWidgetItem*>> & items)
    {
        for(int row = 0; row < items.size(); row++)
        {
            widget->insertRow(row);

            auto columnData = items.at(row);

            for(int column = 0; column < columnData.size(); column++)
            {
                widget->setItem(row, column, columnData.at(column));
            }
        }

        widget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
};

#endif

