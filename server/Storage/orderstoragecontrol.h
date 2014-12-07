#ifndef ORDERSTORAGECONTROL_H
#define ORDERSTORAGECONTROL_H

/*
* orderstoragecontrol.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* OrderStorageControl class:
* - Used to validate orders before they are sent
* - This is a singleton class
*
* Traceability: CT-037
*
* Acknowledgements: None
*/

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include "mainstoragecontrol.h"
#include "../ContentManagement/purchasingdetails.h"

class OrderStorageControl : public QObject
{
    Q_OBJECT

public:
    /* Static Member Function: getOrderStorageControl
     * out: Instance of OrderStorageControl, or nothing, if
     *        the OrderStorageControl instance failed to initialize.
     * Side Effects: None
     * Return Value: True, if the OrderStorageControl object
     *   is properly initialized.
     */
    static bool getOrderStorageControl(QSharedPointer<OrderStorageControl>& ptr);

    // Public interface needed by the Purchasing subsystem
public:

    /* Member Function: allPurchasingDetailsValid
     * in: List of purchasing details to check
     * out: QString to contain any error message in case of failure
     * Side Effects: None
     * Return Value: True, if all PurchasingDetails were found in the database.
     *               False otherwise, or in case of errors.
     */
    bool allPurchasingDetailsValid(
            QVector<PurchasingDetails*>*& purchasingDetails, QString& errorMsg);

protected:
    /* Constructor
     *   Essentially does nothing
     * Side Effects: None
     */
    OrderStorageControl(void);

    /* Member Function: initialize
     * Returns false if this object does not initialize properly.
     */
    bool initialize(void);

private:
    QSharedPointer<MainStorageControl> mainStorage;

private:
    // Singleton instance
    static QSharedPointer<OrderStorageControl> orderStorage;
    static bool isInitialized;
    static bool initializationAttempted;
};

#endif // ORDERSTORAGECONTROL_H
