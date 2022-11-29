const db = require('../database');
const bcrypt = require("bcryptjs");
const dotenv = require('dotenv');
const jwt = require('jsonwebtoken');

const saltRounds = 10;
let tries = 3;

const card = {

  checkLocked: function() {
    db.query("select card_owner,card_number from card",function(err,dbResult){
      console.log("card owner: " + dbResult[0].card_owner);
      if (dbResult[0].card_owner == 'LOCKED') {
          console.log("CARD LOCKED DB CONNECTION CLOSED.");
        db.end();  
      }
    })
  },

  checkLoginTries: function(checkLocked) {
    tries = tries -1;
    console.log("Tries left: "+tries);
    if (tries == 0) {
      db.query("select card_owner,card_number from card",function(err,dbResult){
        return db.query("update card set card_owner = 'LOCKED' where card_number = ?",[dbResult[0].card_number],checkLocked);
      });
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


    checkPin: function(cardNumber, callback) {
      return db.query('SELECT pin_code FROM card WHERE card_number = ?',[cardNumber], callback); 
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
    
    update: function(id,card,callback) {
      bcrypt.hash(card.pin_code,saltRounds,function(err, hashed) {
        return db.query("update card set pin_code = ? where card_number = ?",[hashed,id],callback)
        })
    },
}

function generateAdminAccessToken(admin) {
    dotenv.config();
    return jwt.sign(admin, process.env.MY_TOKEN, { expiresIn: '24h' });
}
module.exports = card;
