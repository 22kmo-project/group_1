const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const card = require('../models/card_model.js');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.card_number && request.body.pin_code){
      const cardNumber = request.body.card_number;
      const cardPin = request.body.pin_code; 

        console.log("\nGiven cardnumber:" + cardNumber + " and pincode:" + cardPin);
        card.checkLocked();

        card.checkPin(cardNumber, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          } else{
            if (dbResult.length > 0) {
              bcrypt.compare(cardPin,dbResult[0].pin_code, function(err,compareResult){
                console.log("database pincode: " + dbResult[0].pin_code);
                if(compareResult == true) {
                  console.log("success");
                  const token = generateAccessToken({ card: cardNumber });
                  response.send(token);
                } else {
                  response.send(card.checkLoginTries());
                  
                }            
              }
              );
            }else {
              response.send(card.checkForAdminLogin(cardNumber,cardPin));
            }
          }
        }
  )}else{
      console.log("card_number or pincode missing");
      response.send(false);
    };

function generateAccessToken(card) {
  dotenv.config();
  return jwt.sign(card, process.env.MY_TOKEN, { expiresIn: '1800s' });
}
});
module.exports=router;