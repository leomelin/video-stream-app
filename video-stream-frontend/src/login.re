open Utils;

[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type state = {
  userName: string,
  password: string,
};

type action =
  | UpdateUserName(string)
  | UpdatePassword(string)
  | Submit;

let component = ReasonReact.reducerComponent("Login");

let make = (~message, _children) => {
  ...component,
  initialState: () => {userName: "", password: ""},
  reducer: (action, state: state) =>
    switch (action) {
    | UpdateUserName(name) => ReasonReact.Update({...state, userName: name})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | Submit =>
      Js.Console.log(
        "username " ++ state.userName ++ " password " ++ state.password,
      );
      ReasonReact.Update(state);
    },
  render: ({state, reduce}) =>
    <div className="App">
      <div className="App-hdr">
        <h3> (str("Log in to video streamer")) </h3>
      </div>
      <form
        onSubmit=(
          reduce(e => {
            ReactEventRe.Synthetic.preventDefault(e);
            Submit;
          })
        )>
        <div className="App-intro">
          <div className="userName">
            <label> (str("User name")) </label>
            <input
              _type="text"
              placeholder="Enter user name"
              name="userName"
              value=state.userName
              onChange=(reduce(e => UpdateUserName(valueFromEvent(e))))
            />
          </div>
          <div className="password">
            <label> (str("Password")) </label>
            <input
              _type="password"
              placeholder="Enter password"
              name="password"
              value=state.password
              onChange=(reduce(e => UpdatePassword(valueFromEvent(e))))
            />
          </div>
          <button _type="submit"> (str("Submit")) </button>
        </div>
      </form>
    </div>,
};