const db = require('../database');
const bcrypt = require("bcryptjs");
const dotenv = require('dotenv');
const jwt = require('jsonwebtoken');

const saltRounds = 10;

let tries = 3;

const card = {

    checkLoginTries: function(cardNumber) {
      tries--;
      console.log("tries left: " + tries +"\ntry again.");
      if (tries == 0) {
        console.log(cardNumber + " card locked, db connection closed.");
      }  
  },

    checkForAdminLogin: function(card_number, pin_code) {
      if (card_number == "admin" && pin_code == "root") {
        console.log("ADMIN LOGIN\n");
        const adminToken = generateAdminAccessToken({admin: card_number});
        return "ADMIN TOKEN: \n" + adminToken;
      } else {
        console.log("card does not exists");
        return false;
      }
    },

    checkPin: function(username, callback) {
      return db.query('SELECT pin_code FROM card WHERE card_number = ?',[username], callback); 
    },

    getById: function(id, callback) {
      return db.query('select * from card where card_number = ?', [id], callback);
    },


    getAll: function(callback) {
      return db.query('select * from card', callback);
    },


    add: function(card, callback) {
      bcrypt.hash(card.pin_code,saltRounds,function(err,hash){
      return db.query(
        'insert into card (card_number, pin_code, debit_credit, id_account, card_owner) values(?,?,?,?,?)',
        [card.card_number, hash, card.debit_credit, card.id_account, card.card_owner],
        callback)
      });
    },


    delete: function(id, callback) {
      return db.query('delete from card where card_number = ?', [id], callback);
    },

    
    update: function(card, callback) {
      bcrypt.hash(card.pin_code,saltRounds,function(err, hash) {
      return db.query(
        'update card set pin_code = ? where card_number = ?',
        [hash,card.card_number],
        callback)
      });
    },
    
    
  };
function generateAdminAccessToken(admin) {
    dotenv.config();
    return jwt.sign(admin, process.env.MY_TOKEN, { expiresIn: '24h' });
}
module.exports = card;
