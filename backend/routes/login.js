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
      
        card.checkPin(cardNumber, function(dbError, dbResult) {
          console.log("Given card number and pincode: "+cardNumber+ " "+ cardPin);
          if(dbError){
            response.json(dbError);
          } else{
            if (dbResult.length > 0) {
              bcrypt.compare(cardPin,dbResult[0].pin_code, function(err,compareResult){
                console.log("database pincode: " + dbResult[0].pin_code);
                if(cardPin == dbResult[0].pin_code) {
                  console.log("success");
                  const token = generateAccessToken({ card: cardNumber });
                  response.send(token);
                } else {
                    console.log("wrong pincode");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("card_number or pincode missing");
      response.send(false);
    }
  }
);

function generateAccessToken(card) {
  dotenv.config();
  return jwt.sign(card, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;