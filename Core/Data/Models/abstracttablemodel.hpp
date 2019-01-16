#ifndef ABSTRACTTABLEMODEL_HPP
#define ABSTRACTTABLEMODEL_HPP

#include <QVector>
#include <QString>
#include <QAbstractTableModel>

#include <Core/Data/dbset.hpp>

template<class TEntity>
class AbstractTableModel : public QAbstractTableModel
{
public:
    AbstractTableModel(QObject * parent, DbSet<TEntity> * dataSet);
    AbstractTableModel(DbSet<TEntity> * dataSet);

    virtual ~AbstractTableModel() { }

    int rowCount(const QModelIndex & index = QModelIndex()) const;
    int columnCount(const QModelIndex & index = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void refresh();

    virtual QVector<QString> getColumns() const = 0;

protected:

    virtual QVariant displayData(const QModelIndex & index) const = 0;
    virtual QVariant displayHeaderData(int section) const;

    DbSet<TEntity> * mDataSet;
    QVector<TEntity> mEntities;
};

template<class TEntity>
AbstractTableModel<TEntity>::AbstractTableModel(QObject * parent, DbSet<TEntity> * dataSet) : QAbstractTableModel(parent)
{
    mDataSet = dataSet;
}

template<class TEntity>
AbstractTableModel<TEntity>::AbstractTableModel(DbSet<TEntity> * dataSet) : AbstractTableModel(nullptr, dataSet)
{

}

template<class TEntity>
int AbstractTableModel<TEntity>::rowCount(const QModelIndex & ) const
{
    return mEntities.size();
}

template<class TEntity>
int AbstractTableModel<TEntity>::columnCount(const QModelIndex & ) const
{
    return getColumns().size();
}

template<class TEntity>
QVariant AbstractTableModel<TEntity>::data(const QModelIndex & index, int role) const
{
    if(index.isValid())
    {
        if (role == Qt::DisplayRole)
        {
            return displayData(index);
        }
    }

    return QVariant();
}

template<class TEntity>
QVariant AbstractTableModel<TEntity>::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            return displayHeaderData(section);
        }
        else if (orientation == Qt::Vertical)
        {
            return QString::number(section);
        }
    }

    return QVariant();
}

template<class TEntity>
void AbstractTableModel<TEntity>::refresh()
{
    beginResetModel();

    mEntities = mDataSet->all();

    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount() - 1, columnCount() - 1);

    emit dataChanged(topLeft, bottomRight);

    endResetModel();
}

template<class TEntity>
QVariant AbstractTableModel<TEntity>::displayHeaderData(int section) const
{
    if(section < getColumns().size())
        return getColumns().at(section);

    return tr("Error - DHD");
}

#endif // ABSTRACTTABLEMODEL_HPP
