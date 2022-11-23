const db = require('../database');
const bcrypt = require("bcryptjs");
//TODO: CARD_NUMBER --> ID:KSI? TOKENIT, LOGIN-ENDPOINT

const saltRounds = 10;



const card = {


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
      return db.query(
        'insert into card (card_number, pin_code, debit_credit, id_account, card_owner) values(?,?,?,?,?)',
        [card.card_number, card.pin_code, card.debit_credit, card.id_account, card.card_owner],
        callback
      );
    },


    delete: function(id, callback) {
      return db.query('delete from card where card_number = ?', [id], callback);
    },

    
    update: function(id, card, callback) {
      return db.query(
        'update card set pin_code = ? where card_number = ?',
        [card.pin_code, id],
        callback
      );
    },
    
  };
  module.exports = card;