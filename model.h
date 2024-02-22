#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H


#include <QStandardItemModel>
#include "studentdatabase.h"

class Model : public QStandardItemModel
{
    Q_OBJECT
public:
    Model(StudentDatabase *db, QObject *parent = nullptr);
    ~Model();

    void initDataModel(StudentDatabase *db);

signals:
    void sig_entryRemoved(int idx);
    void sig_entryAdded();
    void sig_studentAlreadyExists(int roll_id);
    void sig_studentAddedSuccesfully();

public slots:
    void slot_pb_remove_clicked(int idx);
    void slot_addStudent_okButtonClicked(const int roll_id, const std::string name, const std::optional<float> gpa);

private:
    StudentDatabase* p_db;
};

#endif // CUSTOMMODEL_H
