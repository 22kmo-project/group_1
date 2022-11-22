const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const login = require('../models/login_model');
const jwt = require('jsonwebtoken');
const dotenv = require('dotenv');

router.post('/', 
  function(request, response) {
    if(request.body.card_number && request.body.pin_code){
      const card_number = request.body.card_number;
      const pin_code = request.body.pin_code;
      
        login.checkPassword(card_number, function(dbError, dbResult) {
          if(dbError){
            response.json(dbError);
          }
          else{
            if (dbResult.length > 0) {
              bcrypt.compare(pin_code,dbResult[0].pin_code, function(err,compareResult) {
                if(compareResult) {
                  console.log("succes");
                  const token = generateAccessToken({ username: card_number });
                  response.send(token);
                }
                else {
                    console.log("wrong password");
                    response.send(false);
                }			
              }
              );
            }
            else{
              console.log("card_number does not exists");
              response.send(false);
            }
          }
          }
        );
      }
    else{
      console.log("card_number or password missing");
      response.send(false);
    }
  }
);

function generateAccessToken(card_number) {
  dotenv.config();
  return jwt.sign(card_number, process.env.MY_TOKEN, { expiresIn: '1800s' });
}

module.exports=router;