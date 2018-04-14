open Utils;

[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

let component = ReasonReact.statelessComponent("Login");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="App">
      <div className="App-hdr">
        <h3> (str("Log in to video streamer")) </h3>
      </div>
      <form>
        <div className="App-intro">
          <div className="userName">
            <label> (str("User name")) </label>
            <input
              _type="text"
              placeholder="Enter user name"
              name="userName"
            />
          </div>
          <div className="password">
            <label> (str("Password")) </label>
            <input
              _type="password"
              placeholder="Enter password"
              name="password"
            />
          </div>
          <button _type="submit"> (str("Submit")) </button>
        </div>
      </form>
    </div>,
};