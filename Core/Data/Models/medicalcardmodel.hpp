#ifndef MEDICALCARDMODEL_HPP
#define MEDICALCARDMODEL_HPP

#include <QVector>
#include <QAbstractTableModel>

#include "Core/Data/database.hpp"

#include "Core/Data/Models/abstracttablemodel.hpp"
#include "Core/Data/Entities/medicalcard.hpp"

class MedicalCardModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    MedicalCardModel(MedicalCard * card, QObject * parent = nullptr);

    int rowCount(const QModelIndex& parent) const;
    int columnCount(const QModelIndex& parent) const;

    void refresh();

    QVariant data(const QModelIndex& index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    MedicalCard * mCard;
    QVector<CardRecord> mRecords;
};

MedicalCardModel::MedicalCardModel(MedicalCard *card, QObject *parent)
    : QAbstractTableModel(parent), mCard(card)
{

}

int MedicalCardModel::rowCount(const QModelIndex &) const
{
    return mRecords.size();
}

int MedicalCardModel::columnCount(const QModelIndex &) const
{
    return 4;
}

void MedicalCardModel::refresh()
{
    beginResetModel();

    mRecords = mDataSet->all();

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);

    emit dataChanged(topLeft, bottomRight);

    endResetModel();
}

QVariant MedicalCardModel::data(const QModelIndex &index, int role) const
{
    return QVariant("None");
}

QVariant MedicalCardModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0: return "Симптомы";
            case 1: return "Диагноз";
            case 2: return "Дата";
            case 3: return "Врач";
            }
        }
        else if (orientation == Qt::Vertical)
        {
            return QString::number(section);
        }
    }

    return QVariant();
}

#endif // MEDICALCARDMODEL_HPP
