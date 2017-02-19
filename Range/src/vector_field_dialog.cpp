/*********************************************************************
 *  AUTHOR: Tomas Soltys                                             *
 *  FILE:   vector_field_dialog.cpp                                  *
 *  GROUP:  Range                                                    *
 *  TYPE:   source file (*.cpp)                                      *
 *  DATE:   14-th May 2013                                           *
 *                                                                   *
 *  DESCRIPTION: Vector field dialog class definition                *
 *********************************************************************/

#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "session.h"
#include "vector_field_dialog.h"

typedef enum _VariableTreeColumn
{
    VARIABLE_TREE_COLUMN_NAME = 0,
    VARIABLE_TREE_COLUMN_TYPE,
    VARIABLE_TREE_N_COLUMNS
} VariableTreeColumn;

VectorFieldDialog::VectorFieldDialog(uint modelID, QWidget *parent) :
    QDialog(parent),
    modelID(modelID),
    entityID(RConstants::eod)
{
    this->createDialog();
}

VectorFieldDialog::VectorFieldDialog(uint modelID, uint entityID, QWidget *parent) :
    QDialog(parent),
    modelID(modelID),
    entityID(entityID)
{
    this->createDialog();
}

int VectorFieldDialog::exec(void)
{
    int retVal = QDialog::exec();

    if (retVal == QDialog::Accepted)
    {
        RVariableType varType = this->getVariableType();
        QList<SessionEntityID> entities = this->modelTree->getSelected();

        if (varType != R_VARIABLE_NONE && entities.size() > 0)
        {
            Session::getInstance().storeCurentModelVersion(this->modelID,tr("Create vector field"));

            if (this->entityID != RConstants::eod)
            {
                RVectorField &vectorField = Session::getInstance().getModel(this->modelID).getVectorField(this->entityID);

                vectorField.clearElementGroupIDs();

                vectorField.setVariableType(varType);

                for (int i=0;i<entities.size();i++)
                {
                    uint elementGroupId = Session::getInstance().getModel(this->modelID).getEntityGroupID(entities[i].getType(),
                                                                                                          entities[i].getEid());
                    if (elementGroupId == RConstants::eod)
                    {
                        continue;
                    }
                    vectorField.addElementGroupID(elementGroupId);
                }

                RLogger::info("Modified vector field \'%s\'\n",vectorField.getName().toUtf8().constData());
            }
            else
            {
                RVectorField vectorField;

                vectorField.setName(RVariable::getName(varType));
                vectorField.setVariableType(varType);

                for (int i=0;i<entities.size();i++)
                {
                    uint elementGroupId = Session::getInstance().getModel(this->modelID).getElementGroupID(entities[i].getType(),
                                                                                                           entities[i].getEid());
                    vectorField.addElementGroupID(elementGroupId);
                }

                Session::getInstance().getModel(this->modelID).addVectorField(vectorField);
                RLogger::info("Created new vector field \'%s\'\n",vectorField.getName().toUtf8().constData());
            }

            Session::getInstance().setModelChanged(this->modelID);
        }
    }

    return retVal;
}

void VectorFieldDialog::createDialog(void)
{
    QIcon cancelIcon(":/icons/file/pixmaps/range-cancel.svg");
    QIcon okIcon(":/icons/file/pixmaps/range-ok.svg");

    this->resize(500,400);

    QString windowTitleStr = tr("Vector field editor");
    this->setWindowTitle(tr(windowTitleStr.toUtf8().constData()));

    QGridLayout *mainLayout = new QGridLayout;
    this->setLayout (mainLayout);

    QLabel *titleLabel = new QLabel;
    if (this->entityID == RConstants::eod)
    {
        titleLabel->setText(tr("Create new vector field."));
    }
    else
    {
        titleLabel->setText(tr("Modify vector field:")  + " <b>" + Session::getInstance().getModel(modelID).getVectorField(entityID).getName() + "</b>");
    }
    mainLayout->addWidget(titleLabel, 0, 0, 1, 1);

    REntityGroupTypeMask typeMask = R_ENTITY_GROUP_POINT
                                  | R_ENTITY_GROUP_LINE
                                  | R_ENTITY_GROUP_SURFACE
                                  | R_ENTITY_GROUP_VOLUME
                                  | R_ENTITY_GROUP_CUT
                                  | R_ENTITY_GROUP_ISO
                                  | R_ENTITY_GROUP_STREAM_LINE;

    this->modelTree = new ModelTreeSimple(this->modelID,typeMask,this);
    if (this->entityID != RConstants::eod)
    {
        Model &rModel = Session::getInstance().getModel(modelID);
        RVectorField &rVectorField = rModel.getVectorField(entityID);
        const std::vector<unsigned int> groupIDs = rVectorField.getElementGroupIDs();
        this->modelTree->clearSelection();
        for (uint i=0;i<groupIDs.size();i++)
        {
            REntityGroupType entityGroupType;
            uint entityIDNum;
            if (rModel.getEntityID(groupIDs[i],entityGroupType,entityIDNum))
            {
                this->modelTree->selectEntity(this->modelID,entityGroupType,entityIDNum);
            }
        }
    }
    mainLayout->addWidget(this->modelTree, 1, 0, 1, 1);

    QObject::connect(this->modelTree,
                     &QTreeWidget::itemSelectionChanged,
                     this,
                     &VectorFieldDialog::onModelTreeSelectionChanged);

    this->variableTree = new QTreeWidget(this);
    this->variableTree->setSelectionMode(QAbstractItemView::SingleSelection);
    this->variableTree->setColumnCount(VARIABLE_TREE_N_COLUMNS);

    QTreeWidgetItem* headerItem = new QTreeWidgetItem();
    headerItem->setText(VARIABLE_TREE_COLUMN_NAME,QString("Variables"));
    headerItem->setText(VARIABLE_TREE_COLUMN_TYPE,QString("type"));
    this->variableTree->setHeaderItem(headerItem);
    this->variableTree->setColumnHidden(VARIABLE_TREE_COLUMN_TYPE,true);

    Model &rModel = Session::getInstance().getModel(this->modelID);

    for (uint i=0;i<rModel.getNVariables();i++)
    {
        RVariable &rVariable = rModel.getVariable(i);
        if (rVariable.getNVectors() > 1)
        {
            QTreeWidgetItem *itemVariable = new QTreeWidgetItem(this->variableTree);
            itemVariable->setText(VARIABLE_TREE_COLUMN_NAME, rVariable.getName());
            itemVariable->setData(VARIABLE_TREE_COLUMN_TYPE,Qt::DisplayRole,QVariant(rVariable.getType()));
            if (this->entityID != RConstants::eod)
            {
                RVectorField &rVectorField = Session::getInstance().getModel(modelID).getVectorField(entityID);
                itemVariable->setSelected(rVariable.getType() == rVectorField.getVariableType());
            }
        }
    }

    mainLayout->addWidget(this->variableTree, 1, 1, 1, 1);

    QObject::connect(this->variableTree,
                     &QTreeWidget::itemSelectionChanged,
                     this,
                     &VectorFieldDialog::onVariableTreeSelectionChanged);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    mainLayout->addLayout(buttonsLayout, 2, 0, 1, 2);

    QPushButton *cancelButton = new QPushButton(cancelIcon, tr("Cancel"));
    buttonsLayout->addWidget(cancelButton);

    this->okButton = new QPushButton(okIcon, tr("Ok"));
    this->okButton->setEnabled(this->variableTree->selectedItems().size() && this->modelTree->selectedItems().size());
    this->okButton->setDefault(true);
    buttonsLayout->addWidget(this->okButton);

    QObject::connect(cancelButton,&QPushButton::clicked,this,&VectorFieldDialog::reject);
    QObject::connect(okButton,&QPushButton::clicked,this,&VectorFieldDialog::accept);
}

RVariableType VectorFieldDialog::getVariableType(void) const
{
    QList<QTreeWidgetItem*> items = this->variableTree->selectedItems();

    if (items.size() == 0)
    {
        return R_VARIABLE_NONE;
    }

    return RVariableType(items[0]->data(VARIABLE_TREE_COLUMN_TYPE,Qt::DisplayRole).toInt());
}

void VectorFieldDialog::onVariableTreeSelectionChanged(void)
{
    this->okButton->setEnabled(this->variableTree->selectedItems().size() && this->modelTree->selectedItems().size());
}

void VectorFieldDialog::onModelTreeSelectionChanged()
{
    this->okButton->setEnabled(this->variableTree->selectedItems().size() && this->modelTree->selectedItems().size());
}
