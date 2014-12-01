#ifndef BILLINGINFORMATION_H
#define BILLINGINFORMATION_H

/*
* billinginformation.h
* ----------------------
* COMP3004A: cuTPS Project
* Team Name: teaQup
* Author(s):
* Bernard Llanos ID: 100793648
* Brandon Keyes  ID: 100897196
* Analee Chicot  ID: 100822791
* Remy Gratwohl  ID: 100891970
*
* BillingInformation class:
* - the billing information of a user (Student, in particular)
*
* Traceability: ET-021
*
* Acknowledgements: None
*/

#include "../ServerCommunication/serializableqobject.h"
#include <QString>

class BillingInformation : public SerializableQObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName)
    Q_PROPERTY(QString address READ getAddress WRITE setAddress)
    Q_PROPERTY(QString institution READ getInstitution WRITE setInstitution)
public:
    /* Constructor
     *   To be used to create a container for deserialized data.
     * Side Effects: None
     */
    BillingInformation(void);

    /* Constructor
     *   Creates a fully-initialized BillingInformation object
     * in: Name used for billing
     * in: Billing address
     * in: Institution to process payment
     * Side Effects: None
     */
    BillingInformation(const QString& name,
         const QString& address,
         const QString& institution);

    /* Member Function: insertToDataStream
     *   Serialization function, which is overridden to
     *     insert the appropriate type constant
     *     into the data stream before the object's contents
     * inout: Data output stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void insertToDataStream(QDataStream& ds) const;

    /* Member Function: extractFromDataStream
     *   Deserialization function
     * inout: Data input stream
     * Side Effects: None
     * Return Value: None
     */
    virtual void extractFromDataStream(QDataStream& ds);

    QString getName() const { return name; }
    void setName(const QString& n) { name = n; }

    QString getAddress() const { return address; }
    void setAddress(const QString& a) { address = a; }

    QString getInstitution() const { return institution; }
    void setInstitution(const QString& ins) { institution = ins; }

private:
    QString name;
    QString address;
    QString institution;
    /* Note: Account number not provided
     * for security reasons.
     * Like most online purchases,
     * the user would just enter the institution
     * to which they will be redirected to process the payment.
     */
};

#endif // BILLINGINFORMATION_H
