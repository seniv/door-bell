const Telegram = require('telegraf/telegram');

const { tg_bot_token, tg_user_id } = process.env;

const bot = new Telegram(tg_bot_token);

module.exports = async (req, res) => {
  bot.sendMessage(tg_user_id, 'Hello!')
    .then(() => res.send('OK'));
}