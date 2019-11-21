const Telegram = require('telegraf/telegram');

const { bot_token, user_id } = process.env;

const bot = new Telegram(bot_token);

module.exports = async (req, res) => {
  bot.sendMessage(user_id, 'Hello!')
    .then(() => res.send('OK'));
}