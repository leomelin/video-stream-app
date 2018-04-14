let webpack = require('webpack')

module.exports = {
  devtool: 'inline-sourcemap',
  context: __dirname,
  target: "node",
  entry: "./server.js",
  mode: "production",
  output: {
    path: `${__dirname}/dist`,
    publicPath: '/dist',
    filename: "bundle.js"
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader',
        query: {
          presets: ['es2015']
        }
      }
    ]
  }
}
