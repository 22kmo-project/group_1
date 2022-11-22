const db = require('../database');

//TODO: CARD_NUMBER --> ID:KSI? TOKENIT, LOGIN-ENDPOINT

const card = {
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