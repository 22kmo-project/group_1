const db = require('../database');

const login={
  login: function(id, callback) {
      return db.query('SELECT pin_code WHERE card_number = ?',[id], callback); 
    },
    checkPassword: function(card_number,callback){
      return db.query('select pin_code from card where card_number = ?',[card_number], callback);
    }
  }

          
module.exports = login;