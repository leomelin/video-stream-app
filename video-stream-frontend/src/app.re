open Utils;

[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

type streamState =
  | NoStream
  | Created
  | Preview
  | Streaming
  | Stopped;

type state = {
  streamState,
  streamUrl: option(string),
};

type action =
  | CreateStream
  | ReceiveStreamUrl(string)
  | StartPreview
  | StartStream
  | StopStream;

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {streamState: NoStream, streamUrl: None},
  reducer: (action, state: state) =>
    switch (action) {
    | CreateStream =>
      Js.Console.log("creating new stream...");
      let payload = Js.Dict.empty();
      Js.Dict.set(
        payload,
        "query",
        Js.Json.string("mutation { startStreaming(streamKey:\"Shiiit!\") }"),
      );
      ReasonReact.SideEffects(
        (
          self =>
            Js.Promise.(
              Fetch.fetchWithInit(
                "http://localhost:4000/graphql",
                Fetch.RequestInit.make(
                  ~method_=Post,
                  ~body=
                    Fetch.BodyInit.make(
                      Js.Json.stringify(Js.Json.object_(payload)),
                    ),
                  ~headers=
                    Fetch.HeadersInit.make({
                      "Content-Type": "application/json",
                    }),
                  (),
                ),
              )
              |> then_(Fetch.Response.json)
              |> then_(_rg =>
                   resolve(
                     self.send(
                       ReceiveStreamUrl(
                         "https://www.youtube.com/watch?v=_Gtc-GtLlTk",
                       ),
                     ),
                   )
                 )
            )
            |> ignore
        ),
      );
    | ReceiveStreamUrl(url) =>
      ReasonReact.Update({streamState: Created, streamUrl: Some(url)})
    | StartPreview => ReasonReact.Update({...state, streamState: Preview})
    | StartStream => ReasonReact.Update({...state, streamState: Streaming})
    | StopStream =>
      ReasonReact.Update({streamState: Stopped, streamUrl: None})
    },
  render: self =>
    <div className="App">
      <div className="App-hdr"> <h1> (str("Video Streamer")) </h1> </div>
      <button
        className="mui-btn mui-btn--raised mui-btn--primary"
        disabled=(
          switch (self.state.streamState) {
          | NoStream
          | Stopped => Js.false_
          | _ => Js.true_
          }
        )
        onClick=(_e => self.send(CreateStream))>
        (str("Create new video stream"))
      </button>
      <div>
        (
          switch (self.state.streamUrl) {
          | None => ReasonReact.nullElement
          | Some(url) =>
            <div>
              <label> (str("Stream url")) </label>
              <input
                className="inputLink mui-textfield"
                readOnly=Js.true_
                value=url
              />
            </div>
          }
        )
      </div>
      <div>
        (
          switch (self.state.streamState) {
          | Created =>
            <button
              className="mui-btn mui-btn--raised mui-btn--danger"
              onClick=(_e => self.send(StartPreview))>
              (str("Start preview"))
            </button>
          | Preview =>
            <div>
              <button
                className="mui-btn mui-btn--raised mui-btn--danger"
                onClick=(_e => self.send(StartStream))>
                (str("Start streaming"))
              </button>
              <div> (str("Preview")) </div>
            </div>
          | Streaming =>
            <div>
              <button
                className="mui-btn mui-btn--raised mui-btn--danger"
                onClick=(_e => self.send(StopStream))>
                (str("Stop streaming"))
              </button>
              <div> (str("You are live!")) </div>
            </div>
          | Stopped => <div> (str("Stream stopped")) </div>
          | _ => ReasonReact.nullElement
          }
        )
      </div>
      <div>
        (
          switch (self.state.streamState) {
          | Preview
          | Streaming =>
            <iframe
              width="560"
              height="315"
              src="https://www.youtube.com/embed/XYZ123"
              allowFullScreen=Js.true_
            />
          | _ => ReasonReact.nullElement
          }
        )
      </div>
    </div>,
};