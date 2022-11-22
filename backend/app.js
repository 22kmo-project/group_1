var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');


var indexRouter = require('./routes/index');
var cardsRouter = require('./routes/cards');
var accountsRouter = require('./routes/accounts');
var customersRouter = require('./routes/customers');
var transactionsRouter = require('./routes/transactions');
var privilegesRouter = require('./routes/privileges');
var card_privilegesRouter = require('./routes/card_privileges');


var app = express();


app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));


app.use('/', indexRouter);
app.use('/cards', cardsRouter);
app.use('/accounts', accountsRouter);
app.use('/customers', customersRouter);
app.use('/transactions', transactionsRouter);
app.use('/privileges', privilegesRouter);
app.use('/card_privileges', card_privilegesRouter);

module.exports = app;
