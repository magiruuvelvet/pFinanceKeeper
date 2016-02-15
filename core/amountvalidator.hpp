#ifndef AMOUNTVALIDATOR_HPP
#define AMOUNTVALIDATOR_HPP

#include <QValidator>

/** Amount Validator <check for valid amount>
 *
 * NOTES: this is a household book, more than 2 decimals makes no sense here...
 *
 * Valid == 0.00; 0; 0.0 <can be converted to double used for the db>
 * Intermediate == 0.; .0; 10.; .01; etc. <fixup required, append/prepend 0 for valid result>
 * Invalid == [empty]; 0.000 <amount must not exceed 2 decimals and must not be empty>
 *
 */

extern QRegExpValidator *amountValidator;

#endif // AMOUNTVALIDATOR_HPP
